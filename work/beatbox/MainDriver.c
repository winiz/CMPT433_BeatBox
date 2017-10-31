#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "audioMixer.h"

int main(void) {
	printf("Beginning play-back of %s\n", SOURCE_FILE_BASEDRUM);
	AudioMixer_init();
	wavedata_t base;
	wavedata_t hihat;
	wavedata_t snare;

	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_BASEDRUM, &base);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_HIHAT, &hihat);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SNARE, &snare);
	
	
	while(1){
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			if (i == 2 || i== 6){
				AudioMixer_queueSound(&snare);
			}
			else{
			AudioMixer_queueSound(&base);
			}
		}
		AudioMixer_queueSound(&hihat);
		sleep(1);
	}
	}
	AudioMixer_freeWaveFileData(&base);
	AudioMixer_freeWaveFileData(&hihat);
	AudioMixer_freeWaveFileData(&snare);
	AudioMixer_cleanup();

	printf("Done!\n");
	return 0;
}
