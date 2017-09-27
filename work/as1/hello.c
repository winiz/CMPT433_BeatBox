/*
Requirements:
Display hello-world welcome message
Continuously loop through the following:
	1. Count # consecutive iterations joystick has been pressed up
	2. Exit program if joystick-up has been pressed long enough
	3. Display status message for joystick & flashing
	4. Flash the LED as required.
	5. Wait 600ms
Display ending message

Author: 
Xinran Zhang 10:16AM 2017.9.26 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_NUMBER 26
#define JOYSTICK_GPIO_VALUE_PATH "/sys/class/gpio/gpio26/value"

int readFromFile(char *fileName);
void writeToFile(char *fileName, int gpioNum);
_Bool checkIfPressedUp();


int main(int argc, char* argv[])
{	
	int counter = 0;
	int Joystick;
	//_Bool isPressed = checkIfPressedUp();
	
	printf("Hello embedded world! from Xinran Zhang!\n"); //Display hello-world welcome message
	
	//dealing with gpio 26 JoystickUp
		
	writeToFile(GPIO_EXPORT_PATH,GPIO_NUMBER); //equivalent: echo 26 > export
	while (counter < 10){
		if (checkIfPressedUp()){
			Joystick = 1;
			counter++;
		}
		else if (!checkIfPressedUp()){
			Joystick = 0;
			counter = 0;
		}
		printf("Flashing 1 time(s): Joystick = %d & counter = %d\n", Joystick, counter);
	}
	printf("Bye Bye embedded world!\n");//Display ending message
	return 0;
}


int readFromFile(char *fileName){
	FILE *pfile = fopen(fileName, "r");
	int boo;
	if (pfile == NULL){
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		exit(-1);
	}
	
	//read integer
	fscanf(pfile, "%d", &boo);  

	//Close
	fclose(pfile);
	return boo;
}


void writeToFile(char *fileName, int gpioNum){
	FILE *pfile = fopen(fileName, "w");
	if (pfile == NULL) {
		printf("ERROR: Unable to open export file.\n");
		exit(1);
	}

	// Write to data to the file using fprintf():
	fprintf(pfile, "%d", gpioNum);

	// Close the file using fclose():
	fclose(pfile);
}


_Bool checkIfPressedUp(){
	int boo = readFromFile(JOYSTICK_GPIO_VALUE_PATH);
	if (boo == 0){
		return 1;
	}
	else
		return 0;
}

