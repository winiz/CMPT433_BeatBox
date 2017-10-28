#include <alsa/asoundlib.h>
#include "audioMixer.h"

int main(void)
{
	printf("Beginning play-back of %s\n", SOURCE_FILE_SNARE);

	// Configure Output Device
	AudioMixer_init();
	AudioMixer_cleanup();
	printf("Done!\n");
	return 0;
}
