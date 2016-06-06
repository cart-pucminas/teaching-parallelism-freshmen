#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

void OddEvenSort(int a[], int size);
int IsSort(int *array, int size);

int main(int argc, char** argv) {
	int size = 1500000, algorithm, i, *arr, opt;
	arr = malloc(size* sizeof(int));
	srand(time(NULL));
	for (i = 0; i < size; i++) 	
		arr[i] = rand()%size;
	double start, end;
	
	start = omp_get_wtime();

	OddEvenSort(arr, size);
	
	end = omp_get_wtime();

	printf("Tempo: %.3f\n",end - start);
	if(IsSort(arr, size) == 1)	
		printf("Result: Sorted\n");
	else 
		printf("Result: Not Sorted\n");
	return 0;
}



void OddEvenSort(int a[], int size){
	int i, j, aux;
	for(j = 0; j < size; j++) {
		if(j%2 == 1)
		for(i = 1; i < size-1; i += 2){
			if(a[i] > a[i+1]){
				aux = a[i];
				a[i] = a[i+1];
				a[i+1] = aux;
			}
		}
		else
		for(i = 0; i < size-1; i += 2){
			if(a[i] > a[i+1]){
				aux = a[i];
				a[i] = a[i+1];
				a[i+1] = aux;
			}
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
