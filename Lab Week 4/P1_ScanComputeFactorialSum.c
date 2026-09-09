/*
    Write a MPI program using N processes to find 1! + 2! + ... + N!. Use MPI_Scan. Calculate the amount of time taken by each program 
    and the whole program.
*/

#include <mpi.h>
#include <stdio.h>

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

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int sendBuffer;
    int recvBuffer;
    double start;
    double end;
    double localTime;
    double totalStart;
    double totalEnd;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Start time of the whole program
    MPI_Barrier(MPI_COMM_WORLD);
    totalStart = MPI_Wtime();

    // Start time for this process
    start = MPI_Wtime();

    sendBuffer = factorial(rank + 1);

    printf("The process with rank %d has computed the factorial of %d = %d.\n", rank, rank + 1, sendBuffer);

    // Scan performs partial reduction across all processes in the communicator
    MPI_Scan(&sendBuffer, &recvBuffer, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // End time for this process
    end = MPI_Wtime();
    localTime = end - start;

    printf("The process with rank %d has computed the sum of factorials up to %d! = %d in time = %f seconds.\n", rank, rank + 1, recvBuffer, localTime);

    // Make sure all processes have finished
    MPI_Barrier(MPI_COMM_WORLD);

    totalEnd = MPI_Wtime();

    if (rank == 0) {
        printf("\nTotal program time = %f seconds.\n", totalEnd - totalStart);
    }

    MPI_Finalize();

    return 0;
}
