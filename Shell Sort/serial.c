#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

void shellsort(int arr[], int n);
int IsSort(int *array, int size);

int main(int argc, char** argv) {
	int size = 1500000, algorithm, i, *arr, opt;
	arr = malloc(size* sizeof(int));
	srand(time(NULL));
	for (i = 0; i < size; i++) 	
		arr[i] = rand()%size;
	double start, end;
	
	start = omp_get_wtime();

	shellsort(arr, size);
	
	end = omp_get_wtime();

	printf("Tempo: %.3f\n",end - start);
	if(IsSort(arr, size) == 1)	
		printf("Result: Sorted\n");
	else 
		printf("Result: Not Sorted\n");
	return 0;
}



void shellsort(int arr[], int n)
{
    int gap, i, j, temp;
	for (gap = n/2; gap > 0; gap /= 2)
		for(i = gap; i < n; i++) {
			int key = arr[i];
			j = i - gap;
			while (j >= 0 && arr[j] > key){
				arr[j+gap] = arr[j];
				j-=gap;
			}
			arr[j+gap] = key;
		}
 
}

int IsSort(int *array, int size) {
	int i, value = 0;
	for(i = 1; i < size; i++) 
		if(array[i-1] > array[i])
			return 0;
	return 1;
}
