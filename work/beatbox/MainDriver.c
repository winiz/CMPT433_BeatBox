#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "composer.h"
#include "audioMixer.h"

int main(void) {
	printf("Beginning play-back of %s\n", SOURCE_FILE_BASEDRUM);
	AudioMixer_init();

	waveFilesReader();
	
	while (1) {
		drumBeatMode(1);
	}

	waveFilesFreer();
	AudioMixer_cleanup();

	printf("Done!\n");
	return 0;
}
