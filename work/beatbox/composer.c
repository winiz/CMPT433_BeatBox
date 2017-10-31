void beatModeSwich(int mode){
	for (int i = 0; i < 4; i++) {
			AudioMixer_queueSound(&sampleFile);
			sleep(1);
		}
}

void readWaveFilesIntoMemory(void){
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_BASEDRUM, &sampleFile);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_HIHAT, &sampleFile);
	AudioMixer_readWaveFileIntoMemory(SOURCE_FILE_SNARE, &sampleFile);
}