#include <alsa/asoundlib.h>
#include "audioMixer.h"

int main(void)
{
	printf("Beginning play-back of %s\n", SOURCE_FILE_SNARE);
	// Configure Output Device
	wavedata_t file_snare;
	AudioMixer_init();
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SNARE, &file_snare);
//	printf("numSamplesM %d\n",file_snare.numSamples);
	AudioMixer_queueSound(&file_snare);
	AudioMixer_freeWaveFileData(&file_snare);
	AudioMixer_cleanup();
	printf("Done!\n");
	return 0;
}
