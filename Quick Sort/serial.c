#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

void quick(int *a, int left, int right);
void swap(int *a, int i, int j);
int partition(int *a, int left,int right,int pivot);
int IsSort(int *array, int size);

int main(int argc, char** argv) {
	int size = 1500000, algorithm, i, *arr, opt;
	arr = malloc(size* sizeof(int));
	srand(time(NULL));
	for (i = 0; i < size; i++) 	
		arr[i] = rand()%size;
	double start, end;
	
	start = omp_get_wtime();

	OddEvenSort(arr, 0, size);
	
	end = omp_get_wtime();

	printf("Tempo: %.3f\n",end - start);
	if(IsSort(arr, size) == 1)	
		printf("Result: Sorted\n");
	else 
		printf("Result: Not Sorted\n");
	return 0;
}

void quick(int *a, int left, int right)
{
    if (left < right)
    {
        int pivot = (left + right) / 2;
 int pos = partition(a,left,right,pivot);
 quick(a, left, pos - 1);
 quick(a, pos + 1, right);
    }
}

void swap(int *a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int partition(int *a, int left,int right,int pivot)
{
    int pos, i;
    swap(a, pivot, right);
    pos = left;
    for(i = left; i < right; i++)
    {
        if (a[i] < a[right])
        {
            swap(a, i, pos);
            pos++;
        }
    }
    swap(a, right, pos);
    return pos;
}



int IsSort(int *array, int size) {
	int i, value = 0;
	for(i = 1; i < size; i++) 
		if(array[i-1] > array[i])
			return 0;
	return 1;
}
