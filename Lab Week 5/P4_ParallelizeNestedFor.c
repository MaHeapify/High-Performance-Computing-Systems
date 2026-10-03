/*
    Write an OpenMP program to parallelize nested for loop for any program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int n = rand() % 10 + 1;

    printf("\nThe value of N selected is: %d\n\n", n);

    // Using parallel for loop
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Thread %d: i = %d, j = %d\n", omp_get_thread_num(), i, j);
        }
    }

    return 0;
}
