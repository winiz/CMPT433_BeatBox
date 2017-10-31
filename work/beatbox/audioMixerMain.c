#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "audioMixer.h"

int main (void) {
	printf("Beginning play-back of %s\n", SOURCE_FILE_BASEDRUM);
	AudioMixer_init();
	wavedata_t sampleFile;
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_BASEDRUM, &sampleFile);
	for (int i = 0; i < 4; i++) {
		AudioMixer_queueSound(&sampleFile);
		sleep(1);
	}
	AudioMixer_freeWaveFileData(&sampleFile);
	AudioMixer_cleanup();
	
	printf("Done!\n");
	return 0;
}