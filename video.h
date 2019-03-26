
/**
 * Author 2011-2012 Eugene Minov <minov.eug@gmail.com>
 */
 
#include "buffer.h"

/**
 * Include needed headers
 */
extern "C"
{
	#define __STDC_CONSTANT_MACROS

	#ifndef INT64_C
	#define INT64_C(c) (c ## LL)
	#define UINT64_C(c) (c ## ULL)
	#endif

	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libswscale/swscale.h>
}

/**
 * Class to work with video files using 'ffmpeg' library
 */
class Video
{
	bool loaded;						// Is video oppened

	int32_t frameLocation;

	AVFormatContext *pFormatCtx;
	int32_t    		i, videoStream;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	AVFrame         *pFrame;
	AVFrame         *pFrameRGB;
	int             numBytes;
	uint8_t         *buffer;
	AVPacket		packet;
	SwsContext		*img_convert_ctx;

public:
	int32_t totalFrames;
	int32_t width;
	int32_t height;
	int32_t fps;

public:
	/**
	 * Load video from file
	 * @filename - path to the video file we're open
	 */
	void init(const char *filename)
	{
		loaded = false;

		totalFrames = 0;
		width = 0;
		height = 0;
		fps = 0;

		frameLocation = 0;

		pFormatCtx = NULL;
		pCodecCtx = NULL;
		pCodec = NULL;
		pFrame = NULL;
		pFrameRGB = NULL;
		numBytes = 0;
		buffer = NULL;

		av_register_all();

		/*// Open video file
		if(avformat_open_input(&pFormatCtx, filename, NULL, NULL)!=0)
		{
			printf("Couldn't open file '%s'\n", filename);
			return; // Couldn't open file
		}

		// Retrieve stream information
		if(av_find_stream_info(pFormatCtx)<0)
		{
			printf("Couldn't find stream information\n");
			return; // Couldn't find stream information
		}*/

		AVDictionary *options = NULL;
		av_dict_set(&options, "video_size", "640x480", 0);
		av_dict_set(&options, "pixel_format", "rgb24", 0);

		if (avformat_open_input(&pFormatCtx, filename, NULL, &options) < 0)
		{
			printf("Couldn't find stream information\n");
			return; // Couldn't find stream information
		}
		av_dict_free(&options);

		avformat_find_stream_info(pFormatCtx, NULL);
		/*AVDictionaryEntry *e;
		if (e = av_dict_get(options, "", NULL, AV_DICT_IGNORE_SUFFIX))
		{
			printf("Option %s not recognized by the demuxer.\n", e->key);
			return;
		}*/



		// Find the first video stream
		videoStream=-1;
		for(uint32_t i=0; i<pFormatCtx->nb_streams; i++)
		{
			if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
			{
				videoStream=i;
				break;
			}
		}
		if(videoStream==-1)
		{
			printf("Didn't find a video stream\n");
			return; // Didn't find a video stream
		}

		// Get a pointer to the codec context for the video stream
		pCodecCtx = pFormatCtx->streams[videoStream]->codec;

		// get duration
		//double duration = double(pFormatCtx->duration) / AV_TIME_BASE;
		//cout << "Video duration: " << duration << std::endl;

		// Find the decoder for the video stream
		pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
		if(pCodec==NULL)
		{
			printf("Codec not found\n");
			return; // Codec not found
		}

		// Inform the codec that we can handle truncated bitstreams -- i.e.,
		// bitstreams where frame boundaries can fall in the middle of packets
		if(pCodec->capabilities & CODEC_CAP_TRUNCATED)
			pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;

		// Open codec
		if(avcodec_open(pCodecCtx, pCodec)<0)
		{
			printf("Could not open codec\n");
			return; // Could not open codec
		}

			/*//AVDictionary *pm;
			//av_dict_set(&pm, "b", "2.5M", 0);
			pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
			if (!pCodec)
			{
				printf("Codec not found\n");
				return; // Codec not found
			}

			if(pCodec->capabilities & CODEC_CAP_TRUNCATED)
				pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;

			pCodecCtx = avcodec_alloc_context3(pCodec);

			if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
			{
				printf("Could not open codec\n");
				return; // Could not open codec
			}*/



		//printf("Using codec: %s", pCodec->name);


		// Allocate video frame
		pFrame = avcodec_alloc_frame();

		pFrameRGB = avcodec_alloc_frame();

		if(pFrameRGB == NULL)
		{
			printf("Problem with pFrameRGB\n");
			return;
		}

		//Allocate memory for the raw data we get when converting.
		numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
		buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));

		//Associate frame with our buffer
		avpicture_fill((AVPicture *) pFrameRGB, buffer, PIX_FMT_RGB24,
			pCodecCtx->width, pCodecCtx->height);



		img_convert_ctx = NULL;




		totalFrames = pFormatCtx->streams[videoStream]->nb_frames;
		//printf("Frames: %d\n", totalFrames);

		width = pCodecCtx->width;
		height = pCodecCtx->height;
		fps = (pCodecCtx->time_base.den / pCodecCtx->time_base.num) / 2 + 1;
		//printf("W=%d; H=%d\n", width, height);

		printf("  Name: '%s'\n", filename);
		printf(" Width: '%d'\n", width);
		printf("Height: '%d'\n", height);
		printf("   Fps: '%d'\n", fps);
		loaded = true;
	}

	/**
	 * Clear video and reinit object
	 */
	void clear()
	{
		if(!loaded)
			return;

		delete [] buffer;
		//av_free(pFrameYUV);

		// Free the frame
		av_free(pFrame);

		av_free(pFrameRGB);

		// Close the codec
		avcodec_close(pCodecCtx);

		// Close the video file
		av_close_input_file(pFormatCtx);

		if(img_convert_ctx)
			sws_freeContext(img_convert_ctx);
	}


public:
	/**
	 * Constructor
	 * @filename - path to the video file we're open
	 */
	Video(const char *filename)
	{
		init(filename);

		if(!loaded)
			return;

		//if(!totalFrames)
		if(false)
		{
			uint32_t framesCount = 0;

			int isFrameFinished = 0;
			{
				while (av_read_frame(pFormatCtx, &packet) >= 0)
				{
					// Is this a packet from the video stream?
					if (packet.stream_index == videoStream)
					{
						// Decode video frame
						if(avcodec_decode_video2(pCodecCtx, pFrame, &isFrameFinished, &packet) < 0)
							continue;

						// Did we get a video frame?
						if (isFrameFinished)
						{
							framesCount++;

							av_free_packet(&packet);
						}
						else // frame isn't finished. not sure why we'd hit this
						{
							av_free_packet(&packet);
						}
					}
				}
			}

			clear();
			init(filename);

			totalFrames = framesCount;
		}
	}

	/**
	 * Destructor
	 */
	~Video()
	{
		//clear();
	}

public:
	/**
	 * Is video loaded
	 * @return - True if video sucessfully loaded or false otherwise
	 */
	__inline operator bool() const { return loaded; }

public:
	/**
	 * Retrieve next video frame
	 * @colors - reference to image 2D buffer we neen write frame to
	 */
	bool nextFrame(ColoredBuffer &colors)
	{
		int isFrameFinished = 0;

		uint32_t framesCount = 0;
		while (av_read_frame(pFormatCtx, &packet) >= 0)
		{
			// Is this a packet from the video stream?
			if (packet.stream_index == videoStream)
			{
				// Decode video frame
				if(avcodec_decode_video2(pCodecCtx, pFrame, &isFrameFinished, &packet) < 0)
					continue;

				// Did we get a video frame?
				if (isFrameFinished)
				{
					// SCANNING GOES HERE

					framesCount++;

					if(!img_convert_ctx)
					{
						img_convert_ctx = sws_getContext(pCodecCtx->width,
							pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width,
							pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL,
							NULL, NULL);

						if(!img_convert_ctx)
						{
							printf("Can't allocate 'img_convert_ctx'\n");
						}
					}

					sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

					for (int y = 0; y < pCodecCtx->height; y++)
					{
						uint8_t *p = pFrameRGB->data[0] + y * pFrameRGB->linesize[0];

						for (int x = 0; x < pCodecCtx->width; x++)
						{
							BufferRGBA &rgba = colors(x, y);

							rgba[0] = *p; p++;
							rgba[1] = *p; p++;
							rgba[2] = *p; p++;
							rgba[3] = 255;
						}
					}

					av_free_packet(&packet);

					return true;
				}
				else // frame isn't finished. not sure why we'd hit this
				{
					av_free_packet(&packet);
				}
			}
		}

		return false;
	}

};

bool readBMP(const char *filename, ColoredBuffer &colors)
{
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        return false;

    uint8_t info[54];
    fread(info, sizeof(uint8_t), 54, f); // read the 54-byte header

    // extract image height and width from header
	uint32_t *widthP = (uint32_t *)&info[18];
	uint32_t *heightP = (uint32_t *)&info[22];
	uint16_t *bitsP = (uint16_t *)&info[28];
    uint32_t width = *widthP;
    uint32_t height = *heightP;
    uint16_t bits = *bitsP;

	printf("  Name: '%s'\n", filename);
	printf(" Width: '%d'\n", width);
	printf("Height: '%d'\n", height);
	printf("  Bits: '%d'\n", bits);

	if(bits != 24) {
		printf("Error: BMP file is %d bit. Only 24bit images are supported.\n", bits);
		printf("Note: Try to open it in paint.exe and re-save.\n");
		return false;
	}

    uint32_t row_padded = (width*3 + 3) & (~3);
    uint8_t* data = new uint8_t[row_padded];

	colors.resize(width, height);
    for(uint32_t i=0; i<height; ++i) {
        fread(data, sizeof(uint8_t), row_padded, f);
        for(uint32_t j=0; j<width*3; j+=3) {
			colors(j/3, i) = BufferRGBA(data[j+2], data[j+1], data[j+0]);
        }
    }

    fclose(f);
    delete[] data;
	return true;
}
