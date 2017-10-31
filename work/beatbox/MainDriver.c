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
		alternative_drum_beat();
			if(checkIfPressed(JOYSTICK_GPIO_VALUE_PATH_UP)){
				set_Volumn(1);
			}
			if(checkIfPressed(JOYSTICK_GPIO_VALUE_PATH_DOWN)){
				set_Volumn(0);
			}
		}

	waveFilesFreer();
	AudioMixer_cleanup();

	printf("Done!\n");
	return 0;
}
