#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define POT 100

void bubbleSort(int *array, int array_size);

int main(void){
	int i,random_Number,temp;
	int *number_array = malloc ( POT * sizeof(int)); //dynamically allocating an number array

	for (i  =0; i < POT; i++){  //initializing array to number 1 through the size of the array
		number_array[i] = i+1;
	}

	for (i = 0; i < POT; i++){  //for each element in the array, swapping itwith a random element in the array
		random_Number = rand() % POT;
		temp = number_array[i];
		number_array[i] = number_array[random_Number];
		number_array[random_Number] = temp;
	}

	for (i = 0; i < POT; i++){
		printf("random number_array[%d] = %d\n", i, number_array[i]);
	}

	bubbleSort(number_array, POT);

	for (i = 0; i < POT; i++){
			printf("sorted number_array[%d] = %d\n", i, number_array[i]);
		}
	free(number_array);
	return 0;
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
