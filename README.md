# syn2midi
Create pianobooster midi from youtube piano video lessons (Synthesia).

I can't read sheet music very well and prefer to use pianobooster to learn.
It was always upsetting me, the lack of midi files to learn new music in internet.
There's plenty of Synthesia piano video lessons on youtube though..
So here you have it. A youtube video lesson to MIDI converter.

## Usage:
Download video lesson using one of online youtube downloader like this one:
http://en.savefrom.net/1-how-to-download-youtube-video/
So, this video, ror example:
https://www.youtube.com/watch?v=JHdbjCLDg2A

Generate MIDI file using:
syn2midi -m mask.bmp -i IT(2017)-Every27Years(Synthesia).mp4 -o Every27Years.midi
