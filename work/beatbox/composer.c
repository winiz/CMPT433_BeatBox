#include <time.h>
#include "composer.h"
#include "audioMixer.h"

static wavedata_t base;
static wavedata_t hihat;
static wavedata_t snare;

static void tempoControler(double bpm);

void waveFilesReader(void) {
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_BASEDRUM, &base);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_HIHAT, &hihat);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SNARE, &snare);
}

static void tempoControler(double bpm) {
	struct timespec delay;
	long halfBeat = (long) ((60 / bpm / 2) * 1000000);
	delay.tv_sec = 0;
	delay.tv_nsec = (halfBeat % 1000000) * 1000;
	nanosleep(&delay, NULL);
}

void standard_rock_drum_beat(void) {
	// basic standard rock drum beat
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			if (i == 2 || i == 6) {
				AudioMixer_queueSound(&snare);
			} else {
				AudioMixer_queueSound(&base);
			}
		}
		AudioMixer_queueSound(&hihat);
		tempoControler (DEFAULT_BPM);
	}
}

void alternative_drum_beat(void) {
	// drumbeat idea copied from https://www.musikalessons.com/blog/2016/06/basic-drum-beats-for-rock/
	for (int i = 0; i < 8; i++) {
		if (i == 0 || i == 3 || i == 4) {
			AudioMixer_queueSound(&base);
		}
		if (i == 2 || i == 6) {
			AudioMixer_queueSound(&snare);
		}
		AudioMixer_queueSound(&hihat);
		tempoControler (DEFAULT_BPM);
	}
}

void waveFilesFreer(void) {
	AudioMixer_freeWaveFileData(&base);
	AudioMixer_freeWaveFileData(&hihat);
	AudioMixer_freeWaveFileData(&snare);
}
