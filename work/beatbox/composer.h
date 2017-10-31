#ifndef COMPOSER_H
#define COMPOSER_H

#define SOURCE_FILE_BASEDRUM "beatbox-wave-files/100051__menegass__gui-drum-bd-hard.wav"
#define SOURCE_FILE_HIHAT "beatbox-wave-files/100053__menegass__gui-drum-cc.wav"
#define SOURCE_FILE_SNARE "beatbox-wave-files/100059__menegass__gui-drum-snare-soft.wav"

#define MIN_BPM 40
#define MAX_BPM 300
#define DEFAULT_BPM (double)120

void waveFilesReader(void);
void drumBeatMode(int mode);
void waveFilesFreer(void);

#endif
