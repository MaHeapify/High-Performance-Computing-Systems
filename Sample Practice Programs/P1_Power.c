/*
    Write a simple MPI program to find out pow(x, rank) for all the processes where 'x' is the integer constant 
    and 'rank' is the rank of the process.
*/

#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank;
    const int number = 3;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Figure out the value of rank of all the processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Calculate pow(number, rank) for all the processes respectively
    printf("Process with rank %d has computed the value of pow(%d, %d) = %f.", rank, number, rank, pow(number, rank));

    // Release the resources after use
    MPI_Finalize();

    return 0;
}
