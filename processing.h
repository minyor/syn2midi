
/**
 * Author 2011-2012 Eugene Minov <minov.eug@gmail.com>
 */

#ifndef PROCESSING_H
#define PROCESSING_H


/**
 * Class for image proccesing algorithms
 */
class Processing
{
public:
    typedef uint32_t GroupMapIndexesType;					// Data type for group indices

	/**
	 * Class to represent stack of pixels on the image
	 */
    struct Group
    {
		/**
		 * Constructor
		 */
        Group()
        {
            binded = NULL;
            count = 0;

            crystallBinded = NULL;
            crystallCount = 0;

            x = y = r = g = b = 0.0;
        }

		/**
		 * Set root (most first parent) of the group (in 2D pixel stack)
		 * @rootGr - pointer to parent group
		 */
        __inline void root(Group *rootGr) { binded = rootGr; }
		/**
		 * Get root group of the given group (in 2D pixel stack)
		 * @return - root (most first parent) of the group
		 */
        __inline Group *root()
        {
            return binded ? binded->root() : this;
        }
		/**
		 * Get root group of the given group (in 3D pixel stack)
		 * @return - root (most first parent) of the group
		 */
        __inline Group *crystallRoot()
        {
            return crystallBinded ? crystallBinded->crystallRoot() : this;
        }

        Group *binded;								// Pointer to root group (in 2D pixel stack)
        uint32_t count;										// Number of pixels in the current group (in 2D pixel stack)

        Group *crystallBinded;						// Pointer to root group (in 3D pixel stack)
        uint32_t crystallCount;								// Number of pixels in the current group (in 3D pixel stack)

        double x, y;										// Position of the center of the group of pixels
        double r, g, b;										// Average color from all the pixels in the group
    };										// object with tools for helping purpose in image proccesing

private:
    Buffer<Processing::GroupMapIndexesType> groupsMap;		// Indexes to groups in form of one index for each image's pixel
    Group **groups;									// Array with actial group objects
    uint32_t groupsCount;									// Number of groups in use

    float layerSquare;										// Square of pixels in all groups on this image

public:
	Processing();
	~Processing();

public:
	/**
	 * Separating an image to multiple chunks of pixels and create a group for each of them
	 * @pixels - reference to 2D buffer with intensity data of our image
	 * @colors - reference to 2D buffer with color data of our image
	 */
	void regroup(IndexedBuffer &pixels, ColoredBuffer &colors);

public:
	/**
	 * Separating an image to multiple chunks of pixels and create a group for each of them
	 * @mask - reference to 2D bit buffer each element of wich will tell as if corresponded pixel have group
	 * @colors - reference to 2D buffer with color data of our image
	 * @groups - reference to 2D buffer with group indices per each pixel
	 */
	void scan(IndexedBuffer &mask, ColoredBuffer &colors, Buffer<Processing::GroupMapIndexesType> &groups);

public:
	/**
	 * Get reference to the 2D buffer with pixel groups of out image
	 * @return - reference to the buffer with pixel groups
	 */
    __inline Buffer<Processing::GroupMapIndexesType> &getGroupsMap() { return groupsMap; }
	/**
	 * Get reference to the array with all pixel groups in use
	 * @return - reference to the array with all pixel groups in use
	 */
    __inline Group **getGroups() { return groups; }
	/**
	 * Get number of the pixel groups in use
	 * @return - number of the pixel groups in use
	 */
    __inline uint32_t getGroupsCount() { return groupsCount; }

	/**
	 * Get square of pixels in all groups on this image
	 * @return - square of pixels in all groups on this image
	 */
    float getLayerSquare() { return layerSquare; }

};



//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================



/**
 * Constructor
 */
Processing::Processing()
{
	groups = NULL;
	groupsCount = 0;
}
/**
 * Destructor
 */
Processing::~Processing()
{
    for(uint32_t i=0; i<groupsCount; ++i)
    {
        Group *currGroupObj = groups[i];
        delete currGroupObj;
    }

    delete[] groups;
    groups = NULL;
}



/**
 * Separating an image to multiple chunks of pixels and create a group for each of them
 * @pixels - reference to 2D buffer with intensity data of our image
 * @colors - reference to 2D buffer with color data of our image
 */
void Processing::regroup(IndexedBuffer &pixels, ColoredBuffer &colors)
{
    int width = pixels.getW();
    int height = pixels.getH();

    groupsMap.clear();
    groupsMap = Buffer<Processing::GroupMapIndexesType>(width, height);

    for(uint32_t i=0; i<groupsCount; ++i) delete groups[i];
    delete[] groups;
    groups = NULL;
    groupsCount = 0;

    scan(pixels, colors, groupsMap);
}


const int globalGroupsArraySize = 65536;//1024 * 8;					// Max size of the global array with temporary defined pixel groups
uint32_t globalGroupsArrayCount = 0;								// Size of the global array with temporary defined pixel groups in use
Processing::Group *globalGroupsArray[globalGroupsArraySize];	// Globas array with temporary defined pixel groups

/**
 * Separating an image to multiple chunks of pixels and create a group for each of them
 * @mask - reference to 2D bit buffer each element of wich will tell as if corresponded pixel have group
 * @colors - reference to 2D buffer with color data of our image
 * @groups - reference to 2D buffer with group indices per each pixel
 */
void Processing::scan(IndexedBuffer &mask, ColoredBuffer &colors, Buffer<Processing::GroupMapIndexesType> &groupsMask)
{
	typedef Processing::GroupMapIndexesType SpecGroup;
    int width = mask.getW();
    int height = mask.getH();

    int width_1 = width - 1;
    int height_1 = height - 1;

    int i, j;

    globalGroupsArray[0] = new Group;
    SpecGroup counter = 1;
    SpecGroup currGroup = 0;
    SpecGroup lastGroup = 0;

    memset(globalGroupsArray, 0, sizeof(Group *) * globalGroupsArraySize);
    globalGroupsArrayCount = 1;

    for(int y=0; y<height; y++)
        for(int x=0; x<width; x++)
            groupsMask(x, y) = 0;

    for(int y=1; y<height_1; y++)
        for(int x=1; x<width_1; x++)
        {
            groupsMask(x, y) = 0;

            if(mask(x, y) > 0)
            {
            #define pushInline \
                currGroup = groupsMask(i, j);\
                if(currGroup > 0 && lastGroup != currGroup)\
                {\
                    if(lastGroup > 0)\
                    {\
                        Group *currGroupObj = globalGroupsArray[currGroup];\
                        Group *lastGroupObj = globalGroupsArray[lastGroup];\
                        if(currGroupObj && lastGroupObj && currGroupObj != lastGroupObj)\
                        {\
                            Group *rootCurrGroupObj = currGroupObj->root();\
                            Group *rootLastGroupObj = lastGroupObj->root();\
                            if(rootCurrGroupObj != rootLastGroupObj && rootCurrGroupObj != lastGroupObj && rootLastGroupObj != currGroupObj)\
                                rootLastGroupObj->root(rootCurrGroupObj);\
                        }\
                    }\
                    else lastGroup = currGroup;\
                }

                lastGroup = 0;
                i = x - 1; j = y - 1;   pushInline;
                i = x;                  pushInline;
                i = x + 1;              pushInline;
                i = x - 1; j = y;       pushInline;

            #undef pushInline

                if(lastGroup == 0)
                {
                    lastGroup = counter; ++counter;
                    globalGroupsArray[lastGroup] = new Group;
                    ++globalGroupsArrayCount;
                }

                ++globalGroupsArray[lastGroup]->count;
                BufferRGBA &rgba = colors(x, y);
                globalGroupsArray[lastGroup]->x += (float)x;
                globalGroupsArray[lastGroup]->y += (float)y;
                globalGroupsArray[lastGroup]->r += (float)rgba[0];
                globalGroupsArray[lastGroup]->g += (float)rgba[1];
                globalGroupsArray[lastGroup]->b += (float)rgba[2];
                groupsMask(x, y) = lastGroup;
            }
        }

    for(uint32_t i=0; i<globalGroupsArrayCount; ++i)
    {
        Group *currGroupObj = globalGroupsArray[i];
        if(!currGroupObj) continue;
        if(!currGroupObj->binded) continue;

        Group *rootCurrGroupObj = currGroupObj->root();
        rootCurrGroupObj->count += currGroupObj->count;
        rootCurrGroupObj->x += currGroupObj->x;
        rootCurrGroupObj->y += currGroupObj->y;
        rootCurrGroupObj->r += currGroupObj->r;
        rootCurrGroupObj->g += currGroupObj->g;
        rootCurrGroupObj->b += currGroupObj->b;
    }

    groups = new Group *[globalGroupsArrayCount];
    groupsCount = globalGroupsArrayCount;

    for(uint32_t i=0; i<globalGroupsArrayCount; ++i)
    {
        Group *currGroupObj = globalGroupsArray[i];
        groups[i] = currGroupObj;

        if(!currGroupObj) continue;
        if(currGroupObj->binded) continue;

		if(currGroupObj->count)
		{
			currGroupObj->x /= (double)currGroupObj->count;
			currGroupObj->y /= (double)currGroupObj->count;
			currGroupObj->r /= (double)currGroupObj->count;
			currGroupObj->g /= (double)currGroupObj->count;
			currGroupObj->b /= (double)currGroupObj->count;
		}
    }
}



#endif //PROCESSING_H
