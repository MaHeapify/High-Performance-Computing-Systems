// Write a program in MPI where even ranked process prints factorial of the rank and odd ranked process prints rank's Fibonacci number.

#include <mpi.h>
#include <stdio.h>

// Returns the factorial for the given rank
int factorial(int rank) {
    int fact = 1;

    for (int i = rank; i > 1; i--) {
        fact *= i;
    }

    return fact;
}

// Returns the fibonacci number for the given rank considering 0 based indexing
int fibonacci(int rank) {
    int term1 = 0;
    int term2 = 1;
    int nextTerm = 0;

    if (rank == 0 || rank == 1) {
        return rank;
    }

    for (int i = 0; i < rank - 1; i++) {
        nextTerm = term1 + term2;
        term1 = term2;
        term2 = nextTerm;
    }

    return nextTerm;
}

int main(int argc, char *argv[]) {
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank % 2 == 0) {
        // Even ranked process computes factorial of the rank
        printf("Process with rank %d computed factorial of %d = %d.", rank, rank, factorial(rank));
    } else {
        // Odd ranked process computes fibonacci of the rank
        printf("Process with rank %d computed fibonnaci number of %d = %d.", rank, rank, fibonacci(rank));
    }

    MPI_Finalize();

    return 0;
}
