#include <alsa/asoundlib.h>
#include "audioMixer.h"

int main(void)
{
	printf("Beginning play-back of %s\n", SOURCE_FILE_SNARE);
	// Configure Output Device
	wavedata_t sampleFile;
	AudioMixer_init();
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SNARE, &sampleFile);
	AudioMixer_freeWaveFileData(&sampleFile);
	AudioMixer_cleanup();
	printf("Done!\n");
	return 0;
}
