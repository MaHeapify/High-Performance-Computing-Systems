/*
    Write a MPI program to read N values in the root process. Root process sends one value to each process. Every process receives it prints
    the factorial of that number. Use N number of processes.
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Return the factorial of the input number
int factorial(int number) {
    int fact = 1;

    if (number == 0) {
        return fact;
    }

    for (int i = number; i > 0; i--) {
        fact *= i;
    }

    return fact;
}

int main(int argc, char *argv[]) {
    int size;
    int rank;
    int number;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int randomNumber[size];
    
    if (size <= 2) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    if (rank == 0) {
        // Seed for random number generation
        srand(time(NULL));

        for (int i = 0; i < size; i++) {
            // Will generate random numbers in the range of 0 - 9
            randomNumber[i] = rand() % 10;
        }
    }

    // Scatter sends individual messages from the root process to all other processes
    // Send buffer is ignored by all non-root processes
    MPI_Scatter(randomNumber, 1, MPI_INT, &number, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("The process with rank %d has received the value %d from root process with rank 0 and has computed the factorial: %d", rank, number, factorial(number));
    printf("\n");
    
    MPI_Finalize();;

    return 0;
}
