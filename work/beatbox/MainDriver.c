#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

#include "composer.h"
#include "audioMixer.h"
#include "joystickControler.h"
#include "accelerometerControler.h"
#include "udpListener.h"


int main(void) {
	printf("Beginning play-back \n");
	AudioMixer_init();
	UdpListener_startListening();
	joystickControler_init();
	composer_init();
	
	

	UdpListener_cleanup();
	joystickControler_cleanup();
	composer_cleanup();
	AudioMixer_cleanup();
	
	printf("Done!\n");
	return 0;
}
