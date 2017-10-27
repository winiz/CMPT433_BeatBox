#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "sorter.h"

#define POT 100

void* Sorter_thread(void *arg);

void Sorter_startSorting(){
	pthread_create(&idSorter, NULL, Sorter_thread, NULL);
}

void Sorter_stopSorting(){
	pthread_cancel(idSorter);
}

void* Sorter_thread(void *arg){
	int total_sorted_array_count= 0;
	while (1) {
		int i, random_Number, temp;
		total_sorted_array_count++;
		int *number_array = malloc( POT * sizeof(int)); //dynamically allocating an number array

		for (i = 0; i < POT; i++) { //initializing array to number 1 through the size of the array
			number_array[i] = i + 1;
		}

		for (i = 0; i < POT; i++) { //for each element in the array, swapping it with a random element in the array
			random_Number = rand() % POT;
			temp = number_array[i];
			number_array[i] = number_array[random_Number];
			number_array[random_Number] = temp;
		}

//		for (i = 0; i < POT; i++) {
//			printf("random number_array[%d] = %d\n", i, number_array[i]);
//		}

		bubbleSort(number_array, POT);

		free(number_array);
	}
}

void bubbleSort(int *array, int array_size){
	int i, j, temp;
	for(i = 1; i < array_size; i++){
		for (j = 0; j < array_size-i; j++){
			if(array[j] > array[j+1]){
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}
