/**
 * Author 2018 Eugene Minov <minov.eug@gmail.com>
 */
 
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <getopt.h>
#include <set>
#include <functional>

#include "buffer.h"
#include "video.h"
#include "report.h"
#include "processing.h"


using namespace std;

bool saveMidi(const std::string &filename);

enum MIDI_HAND {MIDI_HAND_NONE=0, MIDI_HAND_LEFT=2, MIDI_HAND_RIGHT=3};
void midiKeyBegin(int channel, int time, int key);
void midiKeyEnd(int channel, int time, int key);
void midiAddChannel(int channel, int instrument);
void midiBegin(int ticks);
bool midiEnd(const std::string &filename);

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
	fprintf(stderr, "Usage: %s [-i video file] [-o midi file] [-m mask BMP image file]\n\n", argv[0]);
	fprintf(stderr, "Optional: [-l left hand key colors] [-r right hand key colors]\n");
	fprintf(stderr, "          [-t transpose notes shift, can be negative. 0 is default]\n");
	fprintf(stderr, "          [-s start time in seconds] [-e end time in seconds]\n");
	fprintf(stderr, "          [-R boolean, include to generate report]\n");
	fprintf(stderr, "Defaults are: (make sure there's no spaces in color paremeters)\n");
	fprintf(stderr, "        -l (40,96,167)(112,167,211)(252,182,92)(246,126,16)\n");
	fprintf(stderr, "        -r (237,120,122)(232,79,78)(140,242,44)(92,170,11)\n\n");
	printf("Note: It's recomended for new custom mask image, to open it in paint.exe and re-save it before use.\n");
}

void parceColorConponent(std::string str, BufferRGBA *out) {
	int c = 0;
	auto i = std::string::npos;
	while((i=str.find(',')) != std::string::npos) {
		std::string val = str.substr(0, i);
		str = str.substr(i + 1);
		(*out)[c++] = std::stoi(val);
	}
	(*out)[c] = std::stoi(str);
}
void parceColors(std::string str, BufferRGBA *out) {
	while(str[0] == '(') str = str.substr(1);
	while(str[str.length()-1] == ')') str = str.substr(0, str.length()-1);
	auto i = std::string::npos;
	while((i=str.find(")(")) != std::string::npos) {
		std::string val = str.substr(0, i);
		str = str.substr(i + 2);
		parceColorConponent(val, out++);
	}
	parceColorConponent(str, out);
}

float MINIMUM_DIFF = 10000;

int main(int argc, char **argv)
{
	std::string fileInput;
	std::string fileOutput;
	std::string fileMask;
	std::string colorsStrL;
	std::string colorsStrR;
	int transpose = 0;
    int startTimeInSeconds = 0;
    int endTimeInSeconds = -1;
    bool isCreatingReport = false;

	const uint32_t colorsCount = 10;
	BufferRGBA colors[colorsCount] = {
		BufferRGBA(40, 96, 167),
		BufferRGBA(112, 167, 211),
		BufferRGBA(252, 182, 92),
		BufferRGBA(246, 126, 16),
		
		BufferRGBA(237, 120, 122),
		BufferRGBA(232, 79, 78),
		BufferRGBA(140, 242, 44),
		BufferRGBA(92, 170, 11),
        BufferRGBA(0,0,0),
        BufferRGBA(255,255,255)
	};

	int opt;
	while ((opt = getopt (argc, argv, "i:o:m:l:r:t:s:e:R:h")) != -1)
	{
		switch (opt)
		{
		case 'i': fileInput = optarg; break;
		case 'o': fileOutput = optarg; break;
		case 'm': fileMask = optarg; break;
		case 'l': colorsStrL = optarg; break;
		case 'r': colorsStrR = optarg; break;
		case 't': transpose = stoi(optarg); break;
        case 's': startTimeInSeconds = stoi(optarg); break;
        case 'e': endTimeInSeconds = stoi(optarg); break;
        case 'R': isCreatingReport = string(optarg).compare("true") == 0; break;
		case 'h':
		default: /* '?' */
			printUsage(argc, argv);
			exit(EXIT_FAILURE);
		}
	}
	if(colorsStrL != "") {
		parceColors(colorsStrL, &colors[0]);
	}
	if(colorsStrR != "") {
		parceColors(colorsStrR, &colors[4]);
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
    
    DummyReport dummyReport = DummyReport();
    Report realReport = Report();
    BaseReport *report = isCreatingReport 
        ? (BaseReport*) &realReport 
        : (BaseReport*) &dummyReport; 
    
    cout << "transpose: " << transpose << endl;
    cout << "start: " << startTimeInSeconds << endl;
    cout << "end: " << endTimeInSeconds << endl;
    cout << "isCreatingReport: " << isCreatingReport << endl;

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
	uint32_t fps = video.fps;
	float scale = (float)width / mask.getW();
	ColoredBuffer frame(width, height);
    
	//int ticks = 60; int msPerTick = 1000;
	//int ticks = 120; int msPerTick = 500;
	//int ticks = 326; int msPerTick = 184;
	int ticks = 25; int msPerTick = 500;
	int shiftOctave = 2;
	int shiftNote = notes.size() == 88 ? -3 : 0;
	int shiftKey = shiftOctave * 12 + shiftNote + transpose;
	midiBegin(ticks);
	midiAddChannel(MIDI_HAND_LEFT, 0);
	midiAddChannel(MIDI_HAND_RIGHT, 0);
	{
		BufferRGBA white(255, 255, 255);
		BufferRGBA black(0, 0, 0);
		BufferRGBA left(255, 255, 0);
		BufferRGBA right(255, 0, 0);

		uint32_t framesCount = 0;
		for(uint32_t f=0; video.nextFrame(frame); ++f) {
			float ms = (float(f) / fps) * 1000;
			int time = (ms / msPerTick) * ticks;
            
            int timeInSeconds = ms / 1000; 
            if (timeInSeconds < startTimeInSeconds) {
                continue;
            }
            
            if (endTimeInSeconds != -1 && timeInSeconds > endTimeInSeconds) {
                break;
            }
            
			for(uint32_t n=0; n<notes.size(); ++n) {
				Note &note = notes[n];
				int key = shiftKey + n;
				BufferRGBA color = frame(note.x * scale, note.y * scale);
				BufferRGBA shade = color; shade.contrast(10000.0f);
				float smallerDiff = MINIMUM_DIFF;
				uint32_t fittestColor = 0;
				for(uint32_t c=0; c<colorsCount; ++c) {
					float diff = color.diff(colors[c]);
					if(diff >= smallerDiff) {
                        continue;
                    }
					smallerDiff = diff; fittestColor = c;
				}
                
                if (smallerDiff == MINIMUM_DIFF) {
                    report->recordUnfitColor(color);
                } else {
                    report->recordMatchedColor(colors[fittestColor], color);
                }
                                
                if (note.hand == MIDI_HAND_NONE) {
                    if (fittestColor < 4) {
                        note.hand = MIDI_HAND_LEFT;
                        midiKeyBegin(note.hand, time, key);
                    }
                    else if (fittestColor < 8) {
                        note.hand = MIDI_HAND_RIGHT;
                        midiKeyBegin(note.hand, time, key);
                    }
                    //printf("n=%d c=%d x=%d y=%d color=<%d,%d,%d>\n", n, note.y>320, note.x, note.y, color[0], color[1], color[2]);                    
                }
                if (note.hand != MIDI_HAND_NONE) {
                    if (fittestColor >= 8) {
						midiKeyEnd(note.hand, time, key);
						note.hand = MIDI_HAND_NONE;
					}
				}
			}
			++framesCount;
		}
        
        report->print(colors, colorsCount);
        
		printf("framesCount=%d\n", framesCount);
	}
	midiEnd(fileOutput.c_str());

	return 0;
}
