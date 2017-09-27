/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$$$$$$$$$$$$$$$$$$$$$$Requirements:$$$$$$$$$$$$$$$$$$$$$$$$

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

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_NUMBER 26
#define JOYSTICK_GPIO_VALUE_PATH "/sys/class/gpio/gpio26/value"
#define LED0_TRIGGER_PATH "/sys/class/leds/beaglebone:green:usr0/trigger"
#define LED0_DELAYON_PATH "/sys/class/leds/beaglebone:green:usr0/delay_on"
#define LED0_DELAYOFF_PATH "/sys/class/leds/beaglebone:green:usr0/delay_off"

int readFromFile(char *fileName);
void writeToFile(char *fileName, int gpioNum);
_Bool checkIfPressedUp();
int ledFlashing(int mode);
void busyWait();



int main(int argc, char* argv[])
{	
	int counter = 0;
	int Joystick,mode;
	//_Bool isPressed = checkIfPressedUp();
	
	printf("Hello embedded world! from Xinran Zhang!\n"); //Display hello-world welcome message
	
	//dealing with gpio 26 JoystickUp
		
	writeToFile(GPIO_EXPORT_PATH,GPIO_NUMBER); //equivalent: echo 26 > export
	while (counter < 9){
		if (checkIfPressedUp()){
			mode = ledFlashing(3);
			Joystick = 1;
			counter++;
		}
		else if (!checkIfPressedUp()){
			mode = ledFlashing(1);
			Joystick = 0;
			counter = 0;
		}
		printf("Flashing %d time(s): Joystick = %d & counter = %d\n", mode, Joystick, counter);
		busyWait();
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

	//Close the file 
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
	else {
		return 0;
	}
}

int ledFlashing(int mode){
	// echo timer > trigger
	FILE *pfile = fopen(LED0_TRIGGER_PATH, "w");
	if (pfile == NULL) {
		printf("ERROR: Unable to open export file.\n");
		exit(1);
	}
	fprintf(pfile, "%s", "timer");
	fclose(pfile);
	
	//mode 0 simply means for busywait 600ms 
	if (mode==0){
		writeToFile(LED0_DELAYOFF_PATH, 600);
	}
	//mode 1 simply means flashes once eh
	else if (mode==1){
		writeToFile(LED0_DELAYON_PATH, 100);
		writeToFile(LED0_DELAYOFF_PATH, 100);
	}
	
	//mode 3 simply means triple kills eh
	else if (mode==3){
		writeToFile(LED0_DELAYON_PATH, 30);
		writeToFile(LED0_DELAYOFF_PATH, 30);
		writeToFile(LED0_DELAYON_PATH, 30);
		writeToFile(LED0_DELAYOFF_PATH, 30);
		writeToFile(LED0_DELAYON_PATH, 30);
		writeToFile(LED0_DELAYOFF_PATH, 30);
	}
	return mode;
}

void busyWait(){ //hard coded to 600 ms which is 6e+8 according to duckduckgo
	long seconds = 0;
	long nanoseconds = 600000000;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
	ledFlashing(0);
}
