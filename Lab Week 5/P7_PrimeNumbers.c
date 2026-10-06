/*
    Write an OpenMP program to find the prime numbers from 1 to n employing 
    parallel for directive. Record both serial and parallel execution times.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int checkPrime(int number) {
    if (number < 2) {
        return 0;
    }

	for (int i = 2; i <= sqrt(number); i++) {
		if (number % i == 0) {
			return 0;
		}
	}

	return 1;
}

int main() {
    int n;
    double start, end;
    
    printf("\nEnter the number of elements N: ");
    scanf("%d", &n);
    
    int primeNumbers[n + 1];

    // Serial execution

    // Record the start time
    start = omp_get_wtime();

    for (int i = 2; i <= n; i++) {
        primeNumbers[i] = checkPrime(i);
    }

    // Record the end time
    end = omp_get_wtime();

    // Print the number of seconds elapsed from start till end
    printf("\nSerial execution time: %.9f seconds\n", end - start);

    // Parallel execution

    // Record the start time
    start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 2; i <= n; i++) {
        primeNumbers[i] = checkPrime(i);
    }

    // Record the end time
    end = omp_get_wtime();

    // Print the number of seconds elapsed from start till end
    printf("Parallel execution time: %.9f seconds\n", end - start);

    // Display prime numbers
    printf("\nPrime numbers from 1 to %d:\n", n);

    for (int i = 2; i <= n; i++) {
        if (primeNumbers[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
