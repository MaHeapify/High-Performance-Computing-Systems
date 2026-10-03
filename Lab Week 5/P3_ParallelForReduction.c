/*
    Write an OpenMP program to find the sum of integers from 1 to N
    i) using parallel for loop.
    ii) using reduction clause in parallel for loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int n = rand() % 10 + 1;
    int sum = 0;

    printf("\nThe value of N selected is: %d\n", n);

    // Using parallel for loop
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp atomic
        sum += (i + 1);
    }

    printf("\nThe sum of integers from 1 to N using parallel for loop: %d", sum);

    sum = 0;

    // Using reduction clause in parallel for loop
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += (i + 1);
    }

    printf("\nThe sum of integers from 1 to N using reduction clause in parallel for loop: %d\n", sum);

    return 0;
}
