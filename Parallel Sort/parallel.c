#include <stdio.h>
#include <omp.h>
#include <limits.h>
#include <stdlib.h>


void ParallelSorting(int arr[], int size, void (*Sort)(int *,int));
void mergeSorting(int arr[], int size_chunk, int number_chunk, int remainder);
void bubblesort(int a[], int n);

int main(int argc, char** argv) {
	int size = 15000, algorithm, i, *arr, opt;
	arr = malloc(size* sizeof(int));
	for (i = 0; i < size; i++) 	
		arr[i] = rand()%size;

	ParallelSorting(arr, size, bubblesort);
		
	 return 0;
}


void ParallelSorting(int arr[], int size, void (*Sort)(int *,int))
{
	#pragma omp parallel shared(arr, size) firstprivate(Sort) default(none)
	{
		int  displacement_local, size_local;
		size_local = size/omp_get_num_threads();
		displacement_local = size_local*omp_get_thread_num();
		if(omp_get_thread_num() == omp_get_num_threads()-1)
			size_local = size_local+size-(size_local*omp_get_num_threads());		
		(*Sort)(arr+displacement_local,size_local); 
		#pragma omp barrier
		#pragma omp master
		mergeSorting(arr, size/omp_get_num_threads(), omp_get_num_threads(), size-(size_local*omp_get_num_threads()));
	}	
}

void mergeSorting(int arr[], int size_chunk, int number_chunk, int remainder){
	int i, j, index_tmp, *tmp, index_chunks[number_chunk];	
	tmp = (int*) malloc((size_chunk*number_chunk+remainder) * sizeof(int));
	for(i = 0; i < number_chunk; i++)
		index_chunks[i] = size_chunk*i;
	for(index_tmp = 0; index_tmp < (size_chunk*number_chunk+remainder); index_tmp++){
		int less_number =  INT_MAX;
		int chunk = -1;
		for(j = 0; j < number_chunk; j++){
			if(arr[index_chunks[j]] < less_number && (index_chunks[j] < ((j+1)*size_chunk) || (j==number_chunk-1 && index_chunks[j] < size_chunk*number_chunk+remainder))){
				chunk = j;
				less_number = arr[index_chunks[j]];
			}
		}
		tmp[index_tmp] = arr[index_chunks[chunk]];
		++index_chunks[chunk];
	}
	for(i = 0; i < size_chunk*number_chunk+remainder; i++)
		arr[i] = tmp[i];
	free(tmp);
}


void bubblesort(int a[], int n){
        int aux, i, j;
        for(j=1; j<=n-1; j++) {
		for(i=0; i<n-j; i++) {
			if(a[i]>a[i+1])
			{
                                aux=a[i];
                                a[i]=a[i+1];
				a[i+1]=aux;
                        }
                }
        }
}
