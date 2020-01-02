/**
 * Author 2011-2012 Eugene Minov <minov.eug@gmail.com>
 */

using namespace std;

#include <cstring>
#include <math.h>
#include <sstream>
#include <string>
#include <iomanip>

/**
 * Class to represent a image in form of 2D array
 * @Spec - type o the each element of the array
 */
template<class Spec>
	class Buffer
	{
		Spec **data;	// Image's pixel data
		uint32_t w;		// Width of the image
		uint32_t h;		// Height of the image

	public:
		/**
		 * Constructor from the object of the same type
		 * @value - object of the same class to init from
		 */
		Buffer<Spec>(const Buffer<Spec> &value)
		{
			w = value.w;
			h = value.h;

			//data = (Spec **)malloc(sizeof(Spec *) * h);
			data = (Spec **)new Spec *[h];
			for(uint32_t i=0; i<h; i++)
			{
				//data[i] = (Spec *)malloc(sizeof(Spec) * w);
				data[i] = (Spec *)new Spec[w];
				memcpy(data[i], value.data[i], sizeof(Spec) * w);
			}
		}
		/**
		 * Constructor - initializator
		 * @w - width of the image
		 * @h - height of the image
		 */
		Buffer<Spec>(uint32_t w = 0, uint32_t h = 0)
		{
			this->w = w;
			this->h = h;

			if(!w || !h)
			{
				data = NULL;
				return;
			}

			//data = (Spec **)malloc(sizeof(Spec *) * h);
			data = (Spec **)new Spec *[h];
			for(uint32_t i=0; i<h; i++)
				//data[i] = (Spec *)malloc(sizeof(Spec) * w);
				data[i] = (Spec *)new Spec[w];
		}
		/**
		 * Resize current image (all data will be destroyed)
		 * @w - width of the image
		 * @h - height of the image
		 */
		void resize(uint32_t w, uint32_t h)
		{
			clear();

			this->w = w;
			this->h = h;

			if(!w || !h)
			{
				data = NULL;
				return;
			}

			//data = (Spec **)malloc(sizeof(Spec *) * h);
			data = (Spec **)new Spec *[h];
			for(uint32_t i=0; i<h; i++)
				//data[i] = (Spec *)malloc(sizeof(Spec) * w);
				data[i] = (Spec *)new Spec[w];
		}
		/**
		 * Delete all pixel data and reinit image
		 */
		void clear()
		{
			if(!data)
				return;
			for(uint32_t i=0; i<h; i++)
				delete[] data[i];
			delete[] data;
			data = NULL;

			this->w = 0;
			this->h = 0;
		}
		/**
		 * Destructor
		 */
		~Buffer()
		{
			clear();
		}

	public:
		/**
		 * Operator to access pixel on given coordinates in image space
		 * @x - X coordinate
		 * @y - Y coordinate
		 * @return - pixel data of specified type
		 */
		__inline Spec &operator ()(uint32_t x, uint32_t y)
		{
			return data[y][x];
		}
		/**
		 * Assign from the object of the same type
		 * @value - object of the same class to init from
		 * @return - reference to self
		 */
		const Buffer<Spec> &operator =(const Buffer<Spec> &value)
		{
			this->~Buffer();

			w = value.w;
			h = value.h;

			//data = (Spec **)malloc(sizeof(Spec *) * h);
			data = (Spec **)new Spec *[h];
			for(uint32_t i=0; i<h; i++)
			{
				//data[i] = (Spec *)malloc(sizeof(Spec) * w);
				data[i] = (Spec *)new Spec[w];
				memcpy(data[i], value.data[i], sizeof(Spec) * w);
			}

			return *this;
		}

	public:
		/**
		 * Check for non void object
		 * @return - true if there's at least one pixel stored or false otherwise
		 */
		__inline operator bool () const { return data; }

	public:
		/**
		 * Get image's width
		 * @return - width of the image
		 */
		__inline uint32_t getW() const { return w; }
		/**
		 * Get image's height
		 * @return - height of the image
		 */
		__inline uint32_t getH() const { return h; }

	};

/**
 * Simple structure to store red, green, blue and alpha (transparency)
 * components of the color
 */
struct BufferRGBA
{
	uint32_t rgba;

	BufferRGBA() {};
	BufferRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255) {
		operator[](0) = r; operator[](1) = g; operator[](2) = b; operator[](3) = a;
	};

	void contrast(float factor) {
		for(int i=0; i<3; ++i) {
			uint8_t &c = operator[](i);
			float f =(float(c) - 127) * factor;
			c = uint8_t(std::min(255.0f, std::max(0.0f, f + 127)));
		}
	}

	float diff(BufferRGBA &v) {
		float ret = 0;
		for(int i=0; i<3; ++i) {
			ret += fabsf((float)operator[](i) - (float)v[i]);
		}
		return ret;
	}
    
    string toWebColor() {
        ostringstream osstream;
        osstream << setfill('0') << hex 
            << setw(2) << (uint32_t) operator[](0) 
            << setw(2) << (uint32_t) operator[](1) 
            << setw(2) << (uint32_t) operator[](2) 
            << setw(2) << (uint32_t) operator[](3);
        return osstream.str();
    }

	/**
	 * Component access by index operator
	 * @index - component index (0 - r; 1 - g; 2 - b; 3 - a)
	 * @return reference to 8-bit value represented desired component
	 */
	__inline uint8_t &operator[](uint32_t index) { return ((uint8_t *)&rgba)[index]; }

    bool operator<(const BufferRGBA& rhs) const {
        return rgba < rhs.rgba;
    }
};

#define IndexedBuffer Buffer<uint8_t>
#define ColoredBuffer Buffer<BufferRGBA>
#define FloatBuffer Buffer<float>
