#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

void mergesort(int arr[], int size, int thread);
void Merge(int vec[], int vecSize);
int IsSort(int *array, int size);

int main(int argc, char** argv) {
	int size = 1500000, algorithm, i, *arr, opt;
	arr = malloc(size* sizeof(int));
	srand(time(NULL));
	for (i = 0; i < size; i++) 	
		arr[i] = rand()%size;
	double start, end;
	
	start = omp_get_wtime();

	mergesort(arr, size, 4);
	
	end = omp_get_wtime();

	printf("Tempo: %.3f\n",end - start);
	if(IsSort(arr, size) == 1)	
		printf("Result: Sorted\n");
	else 
		printf("Result: Not Sorted\n");
	return 0;
}



void mergesort(int arr[], int size, int thread){
	int mid;
	if(size > 1) {
		mid = size / 2;
		if(thread > 1) {
			 #pragma omp parallel sections
			{
				#pragma omp section
				{
					mergesort(arr, mid, thread/2);
				}
				#pragma omp section
				{
					mergesort(arr + mid, size - mid, thread/2);
				}
			}
		} else {
			mergesort(arr, mid, 1);
			mergesort(arr + mid, size - mid, 1);		
		}
		Merge(arr, size);
	}
}

void Merge(int vec[], int vecSize) {
	int mid;
	int i, j, k;
	int* tmp;
 
	tmp = (int*) malloc(vecSize * sizeof(int));
	if (!tmp) 
		exit(1);
 
	mid = vecSize / 2;
 
	i = 0;
	j = mid;
	k = 0;
	
	while (i < mid && j < vecSize) {
		if (vec[i] < vec[j]) 
			tmp[k] = vec[i++];
		else 
			tmp[k] = vec[j++];
		++k;
	}
	
	if (i == mid) 
		while (j < vecSize) 
			tmp[k++] = vec[j++];	
	else 
		while (i < mid) 
			tmp[k++] = vec[i++];
	
	for (i = 0; i < vecSize; ++i) 
		vec[i] = tmp[i];
	
	free(tmp);
}

int IsSort(int *array, int size) {
	int i, value = 0;
	for(i = 1; i < size; i++) 
		if(array[i-1] > array[i])
			return 0;
	return 1;
}
