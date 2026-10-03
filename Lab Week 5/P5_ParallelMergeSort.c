/*
    Write an OpenMP program to sort an array of n elements using parallel merge sort 
    with the sections directive.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Perform merge algorithm to merge the 2 arrays together
void merge(int array[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int *tempArr = (int *)malloc((right - left + 1) * sizeof(int));

    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            tempArr[k++] = array[i++];
        } else {
            tempArr[k++] = array[j++];
        }
    }

    while (i <= mid) {
        tempArr[k++] = array[i++];
    }

    while (j <= right) {
        tempArr[k++] = array[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        array[i] = tempArr[k];
    }

    free(tempArr);
}

// Perform merge sort to sort the 2 split arrays individually
void mergeSort(int array[], int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergeSort(array, left, mid);
        }

        #pragma omp section
        {
            mergeSort(array, mid + 1, right);
        }
    }

    merge(array, left, mid, right);
}

int main()
{
    int n;

    printf("\nEnter number of elements: ");
    scanf("%d", &n);

    int *array = (int *)malloc(n * sizeof(int));

    printf("\nEnter the elements of the array:\n", n);
    for (int i = 0; i < n; i++) {
        printf("\nEnter the element %d: ", i);
        scanf("%d", &array[i]);
    }

    printf("\nOriginal array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    mergeSort(array, 0, n - 1);

    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return 0;
}
