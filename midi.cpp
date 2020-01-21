/**
 * Author 2018 Eugene Minov <minov.eug@gmail.com>
 */
 
#include "MidiFile.h"
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////

MidiFile midifile;
int track      = 0;

void midiKeyBegin(int channel, int time, int key) {
   int velocity   = 64;
	midifile.addNoteOn(track, time, channel, key, velocity);
}
void midiKeyEnd(int channel, int time, int key) {
   int velocity   = 64;
	midifile.addNoteOff(track, time, channel, key, velocity);
}
void midiAddChannel(int channel, int instrument) {
	midifile.addPatchChange(track, 0, channel, instrument); // 0=piano
}
void midiBegin(int ticks) {
	midifile = MidiFile();
	midifile.setTicksPerQuarterNote(ticks); // ticks per quarter note
	midifile.addTrackName(track, 0, "Melody");
}
bool midiEnd(const std::string &filename) {
   midifile.sortTracks();         // ensure tick times are in correct order
   midifile.write(filename.c_str()); // write Standard MIDI File twinkle.mid
   return true;
}
