/*
    Create a program where multiple threads calculate factorial of different 
    numbers in parallel.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Computes the factorial of a given number
int factorial(int number) {
    int fact = 1;

    if (number == 0 || number == 1) {
        return fact;
    }

    for (int i = number; i > 0; i--) {
        fact *= i;
    }

    return fact;
}

int main() {
    srand(time(NULL));

    int randomSize = rand() % 10;
    int randomNumbers[randomSize];

    // Generate a list of random numbers for the threads to compute factorial of
    for (int i = 0; i < randomSize; i++) {
        randomNumbers[i] = rand() % 13;
    }

    #pragma omp parallel for
    for (int i = 0; i < randomSize; i++) {
        int threadId = omp_get_thread_num();

        printf("\nThread ID %d computed factorial of %d: %d", threadId, randomNumbers[i], factorial(randomNumbers[i]));
    }
    printf("\n");

    return 0;
}
