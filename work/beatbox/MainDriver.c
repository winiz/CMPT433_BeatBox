#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "composer.h"
#include "audioMixer.h"
#include "joystickControler.h"



int main(void) {
	printf("Beginning play-back \n");
	AudioMixer_init();
	joystickControler_init();
	composer_init();
	
	joystickControler_cleanup();
	composer_cleanup();
	AudioMixer_cleanup();
	
	printf("Done!\n");
	return 0;
}
