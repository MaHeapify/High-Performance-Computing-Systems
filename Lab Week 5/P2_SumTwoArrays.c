/*
	Write an OpenMP program to sum the respective elements of the two arrays.
	i) using number of threads equal to the number of CPU cores.
	ii) using number of threads irrespective of number of CPU cores.	
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void randomlyPopulateArray(int array[], int size) {
	int randomNumber;
	
	for (int i = 0; i < size; i++) {
   		randomNumber = rand() % 10;
		array[i] = randomNumber;	
	}
}

// Prints the array elements
void displayArray(int array[], int size) {
   for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
   }
}

int main() {
	srand(time(NULL));
	
	// Current system contains number of CPU cores = 8
	// Using number of threads equal to number of CPU cores by default (8 CPU cores in this case)
	
	int size = 8;
	int array1[size];
	int array2[size];
	int array3[size];
	
	// Randomly populate the array
	randomlyPopulateArray(array1, size);
	randomlyPopulateArray(array2, size);
	
	printf("\nArray 1 elements: ");
	displayArray(array1, size);
	
	printf("\nArray 2 elements: ");
	displayArray(array2, size);
		
	#pragma omp parallel
	{	
		int threadId = omp_get_thread_num();
		array3[threadId] = array1[threadId] + array2[threadId];
	}
	
	printf("\nArray 3 elements (after summing corresponding elements of Array 1 and Array 2): ");
	displayArray(array3, size);
	
	// Using number of threads equal to number of CPU cores by default
	size = 8;
	int array4[size];
	int array5[size];
	int array6[size];
	
	// Randomly populate the array
	randomlyPopulateArray(array4, size);
	randomlyPopulateArray(array5, size);
	
	printf("\nArray 1 elements: ");
	displayArray(array4, size);

	printf("\nArray 2 elements: ");
	displayArray(array5, size);
	
	#pragma omp parallel num_threads(size)
	{	
		int threadId = omp_get_thread_num();
		array6[threadId] = array4[threadId] + array5[threadId];
	}
	
	printf("\nArray 3 elements (after summing corresponding elements of Array 1 and Array 2): ");
	displayArray(array6, size);
	printf("\n");
	
	return 0;
}
