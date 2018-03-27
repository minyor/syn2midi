/**
 * Author 2018 Eugene Minov <minov.eug@gmail.com>
 */
 
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <getopt.h>

#include "video.h"
#include "processing.h"

bool saveMidi(const std::string &filename);

enum MIDI_HAND {MIDI_HAND_NONE=0, MIDI_HAND_LEFT=2, MIDI_HAND_RIGHT=3};
void miniKeyBegin(int channel, int time, int key);
void miniKeyEnd(int channel, int time, int key);
void miniAddChannel(int channel, int instrument);
void miniBegin(int ticks);
bool miniEnd(const std::string &filename);

struct Note {
	MIDI_HAND hand = MIDI_HAND_NONE;
	uint32_t x = 0, y = 0;
	static bool compare(const Note &e1, const Note &e2) { return e2.x > e1.x; }
};

bool extractNotePos(ColoredBuffer &mask, BufferRGBA color, std::vector<Note> &notes) {
	IndexedBuffer pixels(mask.getW(), mask.getH());
	for(uint32_t y=0; y<mask.getH(); ++y) {
		for(uint32_t x=0; x<mask.getW(); ++x) {
			pixels(x, y) = mask(x, y).rgba == color.rgba ? 255 : 0;
		}
	}

	Processing proc;
	proc.regroup(pixels, mask);
	{
		Processing::Group **groups = proc.getGroups();
		uint32_t groupsCount = proc.getGroupsCount();

		uint32_t actualGroupsCount = 0;
		for(uint32_t g=0; g<groupsCount; g++) {
			Processing::Group *group = groups[g];
			if(!group || group->binded) continue;
			actualGroupsCount++;
		}
		notes.resize(actualGroupsCount);
		for(uint32_t g=0, f=0; g<groupsCount; g++) {
			Processing::Group *group = groups[g];
			if(!group || group->binded) continue;

			Note &note = notes[f++];
			note.x = group->x;
			note.y = mask.getH() - group->y;
		}
	}
	std::sort(notes.begin(), notes.end(), Note::compare);
	return notes.size();
}

void printUsage(int argc, char **argv) {
	fprintf(stderr, "Usage: %s [-i video file] [-o midi file] [-m mask BMP image file]\n", argv[0]);
	printf("Note: It's recomended for new custom mask image, to open it in paint.exe and re-save it before use.\n");
}

int main(int argc, char **argv)
{
	std::string fileInput;
	std::string fileOutput;
	std::string fileMask;
	int opt;
	while ((opt = getopt (argc, argv, "i:o:m:")) != -1)
	{
		switch (opt)
		{
		case 'i': fileInput = optarg; break;
		case 'o': fileOutput = optarg; break;
		case 'm': fileMask = optarg; break;
		case 'h':
		default: /* '?' */
			printUsage(argc, argv);
			exit(EXIT_FAILURE);
		}
	}
	if(fileInput == "" || fileOutput == "" || fileMask == "") {
		fprintf(stderr, "Error: -i, -o and -m args are mandatory!\n");
		printUsage(argc, argv);
		exit(EXIT_FAILURE);
	}

	ColoredBuffer mask;
	if(!readBMP(fileMask.c_str(), mask)) {
		fprintf(stderr, "Error: Cannot load mask image.\n");
		exit(EXIT_FAILURE);
	}

	std::vector<Note> notes;
	extractNotePos(mask, BufferRGBA(0, 0, 255), notes);
	printf("notes=%d\n", notes.size());

	Video video(fileInput.c_str());
	if(!video) {
		printf("Error: Can't load video '%s'.\n", fileInput.c_str());
		exit(EXIT_FAILURE);
	}

	uint32_t width = (uint32_t)video.width;
	uint32_t height = (uint32_t)video.height;
	uint32_t fps = 30;
	float scale = (float)width / mask.getW();
	ColoredBuffer frame(width, height);

	//int ticks = 60; int msPerTick = 1000;
	//int ticks = 120; int msPerTick = 500;
	//int ticks = 326; int msPerTick = 184;
	int ticks = 26; int msPerTick = 500;
	int shiftOctave = 2;
	int shiftKey = shiftOctave * 12;
	miniBegin(ticks);
	miniAddChannel(MIDI_HAND_LEFT, 0);
	miniAddChannel(MIDI_HAND_RIGHT, 0);
	{
		BufferRGBA white(255, 255, 255);
		BufferRGBA black(0, 0, 0);
		BufferRGBA left(255, 255, 0);
		BufferRGBA right(255, 0, 0);
		
		const uint32_t colorsCount = 4;
		BufferRGBA colors[colorsCount] = {BufferRGBA(252, 182, 92), BufferRGBA(246, 126, 16), BufferRGBA(237, 120, 122), BufferRGBA(232, 79, 78)};
		uint32_t framesCount = 0;
		for(uint32_t f=0; video.nextFrame(frame); ++f) {
			float ms = (float(f) / fps) * 1000;
			int time = (ms / msPerTick) * ticks;
			for(uint32_t n=0; n<notes.size(); ++n) {
				Note &note = notes[n];
				int key = shiftKey + n;
				BufferRGBA color = frame(note.x * scale, note.y * scale);
				BufferRGBA shade = color; shade.contrast(10000.0f);
				float smallerDiff = 10000;
				uint32_t fittestColor = 0;
				for(uint32_t c=0; c<colorsCount; ++c) {
					float diff = color.diff(colors[c]);
					if(diff >= smallerDiff) continue;
					smallerDiff = diff; fittestColor = c;
				}
				if(shade.rgba != white.rgba && shade.rgba != black.rgba) {
					if(note.hand == MIDI_HAND_NONE) {
						if(fittestColor < 2) {
							note.hand = MIDI_HAND_LEFT;
							miniKeyBegin(note.hand, time, key);
						}
						else {
							note.hand = MIDI_HAND_RIGHT;
							miniKeyBegin(note.hand, time, key);
						}
					}
					//printf("n=%d c=%d x=%d y=%d color=<%d,%d,%d>\n", n, note.y>320, note.x, note.y, color[0], color[1], color[2]);
				}
				else {
					if(note.hand != MIDI_HAND_NONE) {
						miniKeyEnd(note.hand, time, key);
						note.hand = MIDI_HAND_NONE;
					}
				}
			}
			++framesCount;
		}
		printf("framesCount=%d\n", framesCount);
	}
	miniEnd(fileOutput.c_str());

	return 0;
}
