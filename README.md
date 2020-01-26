# syn2midi
Create pianobooster midi from youtube piano video lessons (Synthesia).

I can't read sheet music very well and prefer to use pianobooster to learn.
It was always upsetting me, the lack of midi files to learn new music in internet.
There's plenty of Synthesia piano video lessons on youtube though..
So here you have it. A youtube video lesson to MIDI converter.

## Installation:
- For Windows, download and unpack lattest binary archive from here:
https://github.com/minyor/syn2midi/releases
- For other OS'ses you have to compile it using CodeLite IDE or similar tools

## Usage:
- Download video lesson using one of online youtube downloaders like this one:
http://en.savefrom.net/1-how-to-download-youtube-video/
So, this video, for example (make sure to select mp4 conversion format):
https://www.youtube.com/watch?v=JHdbjCLDg2A
- Choose which mask image best suits your video (82 or 88 notes).
- Generate MIDI file using:
	syn2midi -m mask.bmp -i Every27Years.mp4 -o Every27Years.midi

## Custom key colors:
Optionally you can specify up to 8 key colors to use in notes parsing, 4 colors for left hand and 4 for right hand.
For example, here are the default colors (make sure there's no spaces in color paremeters):

syn2midi -m mask.bmp -i Every27Years.mp4 -o Every27Years.midi -l (40,96,167)(112,167,211)(252,182,92)(246,126,16) -r (237,120,122)(232,79,78)(140,242,44)(92,170,11)

## Other options:
Optional: [-t transpose notes shift, can be negative -t-1. 0 is default]

Optional: [-s start time in seconds] [-e end time in seconds]

Optional: [-R boolean, include to generate report]

## Note:
Not all synthesia videos you find will work with included mask images. You might need to create your own mask.
