#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

void SelectionSort (int *array, int size);
int IsSort(int *array, int size);

int main(int argc, char** argv) {
	int size = 15000, algorithm, i, *arr, opt;
	arr = malloc(size* sizeof(int));
	srand(time(NULL));
	for (i = 0; i < size; i++) 	
		arr[i] = rand()%size;
	double start, end;
	
	start = omp_get_wtime();

	SelectionSort(arr, size);
	
	end = omp_get_wtime();

	printf("Tempo: %.3f\n",end - start);
	if(IsSort(arr, size) == 1)	
		printf("Result: Sorted\n");
	else 
		printf("Result: Not Sorted\n");
	return 0;
}

void SelectionSort (int *array, int size) {
	int i, j, min;
	for (i = 0; i < (size-1); i++) {
		min = i;
		for (j = (i+1); j < size; j++)
			if(array[j] < array[min]) 
					min = j;
		if (i != min) {
			int swap = array[i];
			array[i] = array[min];
			array[min] = swap;
		}
	}
}

int IsSort(int *array, int size) {
	int i, value = 0;
	for(i = 1; i < size; i++) 
		if(array[i-1] > array[i])
			return 0;
	return 1;
}
