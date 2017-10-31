#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "composer.h"
#include "audioMixer.h"
#include "joystickControler.h"

void busyWait(){ //hard coded to 600 ms which is 6e+8 according to duckduckgo
	long seconds = 0;
	long nanoseconds = 600000000;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}

int main(void) {
	printf("Beginning play-back of %s\n", SOURCE_FILE_BASEDRUM);
	AudioMixer_init();

	waveFilesReader();
	
	while (1){
			while (checkIfPressedUp()){
				standard_rock_drum_beat();
			}
			busyWait();
		}

	waveFilesFreer();
	AudioMixer_cleanup();

	printf("Done!\n");
	return 0;
}
