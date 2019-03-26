# syn2midi
Create pianobooster midi from youtube piano video lessons (Synthesia).

I can't read sheet music very well and prefer to use pianobooster to learn.
It was always upsetting me, the lack of midi files to learn new music in internet.
There's plenty of Synthesia piano video lessons on youtube though..
So here you have it. A youtube video lesson to MIDI converter.

## Usage:
- Download video lesson using one of online youtube downloaders like this one:
http://en.savefrom.net/1-how-to-download-youtube-video/
So, this video, for example:
https://www.youtube.com/watch?v=JHdbjCLDg2A
- Choose which mask image best suits your video (82 or 88 notes).
- Generate MIDI file using:
syn2midi -m mask.bmp -i Every27Years.mp4 -o Every27Years.midi

Note: not all synthesia videos, you find, will work with 2 included mask images. You might need to create your own mask.
