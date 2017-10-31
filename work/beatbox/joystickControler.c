#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include "joystickControler.h"
#include "audioMixer.h"


static pthread_t joystickInputCapturethreadId;
static int readFromFile(char *fileName);
static void pinExporter(int value);
void* joystickInputCapturethread(void* arg);

void joystickControler_init(void) {
	pinExporter (JOYSTICK_GPIO_VALUE_UP);
	pinExporter (JOYSTICK_GPIO_VALUE_RIGHT);
	pinExporter (JOYSTICK_GPIO_VALUE_DOWN);
	pinExporter (JOYSTICK_GPIO_VALUE_LEFT);
	pinExporter (JOYSTICK_GPIO_VALUE_IN);
	pthread_create(&joystickInputCapturethreadId, NULL,
			joystickInputCapturethread, NULL);
}

static void pinExporter(int gpioNum) {
	FILE *pfile = fopen(GPIO_EXPORT_PATH, "w");
	if (pfile == NULL) {
		printf("ERROR: Unable to open export file.\n");
		exit(1);
	}

	// Write to data to the file using fprintf():
	fprintf(pfile, "%d", gpioNum);

	// Close the file using fclose():
	fclose(pfile);
}

static int readFromFile(char *fileName) {
	FILE *pfile = fopen(fileName, "r");
	int boo;
	if (pfile == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		exit(-1);
	}
	//read integer
	fscanf(pfile, "%d", &boo);
	//Close the file 
	fclose(pfile);
	return boo;
}

_Bool checkIfPressed(char *fileName) {
	int boo = readFromFile(fileName);
	if (boo == 0) {
		printf("pressed\n");
		return 1;
	} else {
		return 0;
	}
}

void busyWait(void) { //hard coded to 600 ms which is 6e+8 according to duckduckgo
	int seconds = 0;
	long nanoseconds = 600000000;
	struct timespec reqDelay = { seconds, nanoseconds };
	nanosleep(&reqDelay, (struct timespec *) NULL);
}

void set_Volumn(_Bool isUP) {
	int offset = 0;
	if (isUP) {
		offset = 5;
	} else {
		offset = -5;
	}
	int Volume_To_Be_Set = AudioMixer_getVolume() + offset;

	if (Volume_To_Be_Set > MAX_VOL) {
		printf("Maximum Volumn Reached!\n");
		Volume_To_Be_Set = 100;
	} else if (Volume_To_Be_Set < MIN_VOL) {
		printf("Minimum Volumn Reached!\n");
		Volume_To_Be_Set = 100;
	}
	AudioMixer_setVolume(Volume_To_Be_Set);
}

void joystickControler_cleanup(void) {
	pthread_join(joystickInputCapturethreadId, NULL);
}

void* joystickInputCapturethread(void* arg) {
	while (1) {
		if (checkIfPressed (JOYSTICK_GPIO_VALUE_PATH_UP)) {
			set_Volumn(1);
		}
		if (checkIfPressed (JOYSTICK_GPIO_VALUE_PATH_DOWN)) {
			set_Volumn(0);
		}
		busyWait();
	}
}
