#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "composer.h"
#include "audioMixer.h"
#include "joystickControler.h"



int main(void) {
	printf("Beginning play-back of %s\n", SOURCE_FILE_BASEDRUM);
	AudioMixer_init();
	joystickControler_init();

	waveFilesReader();
	
	while (1){
			while (checkIfPressed(JOYSTICK_GPIO_VALUE_PATH_UP)){
				standard_rock_drum_beat();
			}
			while (checkIfPressed(JOYSTICK_GPIO_VALUE_PATH_DOWN)){
				alternative_drum_beat();
			}
			busyWait();
		}

	waveFilesFreer();
	AudioMixer_cleanup();

	printf("Done!\n");
	return 0;
}
