// sorter.h
// Module to spawn a separate thread to sort random arrays
// (permutations) on a background thread. It provides access to
// contents of the current (potentially partially sorted) array,
// and to the count of the total number of arrays sorted.
#ifndef _SORTER_H_
#define _SORTER_H_

pthread_t idSorter;
// Begin/end the background thread which sorts random permutations.
void Sorter_startSorting(void);
void Sorter_stopSorting(void);

// Set/get the size of the array to sort.
// Setting the size changes the size of the next array to sort
void Sorter_setArraySize(int newSize);
int Sorter_getArrayLength(void);

// Get a copy of the current (potentially partially sorted) array.
// Returns a newly allocated array and sets 'length' to be the
// number of elements in the returned array (output parameter only).
// Calling code must call free()
int* Sorter_getArrayData(int *length);

// Get the number of arrays which have finished being sorted.
long long Sorter_getNumberArraysSorted(long long *NumberArraysSorted);

void bubbleSort(int *array, int array_size);

#endif
