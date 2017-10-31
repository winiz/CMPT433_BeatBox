#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "joystickControler.h"

static int readFromFile(char *fileName);

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

_Bool checkIfPressedUp() {
	int boo = readFromFile(JOYSTICK_GPIO_VALUE_PATH);
	if (boo == 0) {
		printf("pressed up\n");
		return 1;
	} else {
		return 0;
	}
}
