#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include "composer.h"
#include "audioMixer.h"

static wavedata_t base;
static wavedata_t hihat;
static wavedata_t snare;
static double Tempo = DEFAULT_BPM;
static int whichBeat = 2;
static pthread_t composerthreadId;
void* composerthread(void* arg);

static void tempoControler(double bpm);

void composer_init(void) {
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_BASEDRUM, &base);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_HIHAT, &hihat);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SNARE, &snare);
	pthread_create(&composerthreadId, NULL, composerthread, NULL);
}

static void tempoControler(double bpm) {
	struct timespec delay;
	long halfBeat = (long) ((60 / bpm / 2) * 1000000);
	delay.tv_sec = 0;
	delay.tv_nsec = (halfBeat % 1000000) * 1000;
	nanosleep(&delay, (struct timespec *) NULL);
}

double composer_getTempo(void) {
	printf("original tempo is %d \n", (int) Tempo);
	return Tempo;
}

void composer_setTempo(double newTempo) {
	Tempo = newTempo;
	printf("current tempo is %d \n", (int) Tempo);
}

void composer_switchBeat(void) {
	if (whichBeat < 3) {
		whichBeat++;
	} else {
		whichBeat = 1;
	}
	printf("current beatMode is %d \n", whichBeat);
}

void composer_setwhichBeat(int BeatUwant) {
	whichBeat = BeatUwant;
}

void no_drum_beat(void) {
	for (int i = 0; i < 8; i++) {
			tempoControler(Tempo);
		}
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
		tempoControler(Tempo);
	}
}

void composer_queueSound(int sound){
	switch (sound) {
			case 1:
				AudioMixer_queueSound(&base);
				break;
			case 2:
				AudioMixer_queueSound(&snare);
				break;
			case 3:
				AudioMixer_queueSound(&hihat);
				break;
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
		tempoControler(Tempo);
	}
}

void composer_cleanup(void) {
	AudioMixer_freeWaveFileData(&base);
	AudioMixer_freeWaveFileData(&hihat);
	AudioMixer_freeWaveFileData(&snare);
	pthread_join(composerthreadId, NULL);
}

void* composerthread(void* arg) {
	while (1) {
		switch (whichBeat) {
		case 1:
			no_drum_beat();
			break;
		case 2:
			standard_rock_drum_beat();
			break;
		case 3:
			alternative_drum_beat();
			break;
		}
	}
}
