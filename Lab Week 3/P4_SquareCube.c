/*
    Write a program to read a value M and N x M number of elements in the root. 
    Using N processes do the following task: Find the square of first M numbers, Find the cube of next 
    M numbers and so on. Print the results in the root.
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void compute(int recvData[], int value, int power) {
    for (int i = 0; i < value; i++) {
        recvData[i] = (int)pow(recvData[i], power);
    }
}

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int value;
    int numberOfElements;
    int *data;
    int *recvData;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        srand(time(NULL));

        // Generate a random number in the range of 1 to 9
        value = rand() % 9 + 1;

        numberOfElements = size * value;

        data = malloc(numberOfElements * sizeof(int));

        printf("Original data:\n");
        for (int i = 0; i < numberOfElements; i++) {
            data[i] = rand() % 10;
            printf("%d ", data[i]);
        }

        printf("\n");
    }

    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    numberOfElements = size * value;

    int rootRecvData[numberOfElements];

    recvData = malloc(value * sizeof(int));

    MPI_Scatter(data, value, MPI_INT, recvData, value, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process computes its assigned power starting from 2
    compute(recvData, value, rank + 2);

    MPI_Gather(recvData, value, MPI_INT, rootRecvData, value, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nModified data with M = %d:\n", value);
        for (int i = 0; i < numberOfElements; i++) {
            printf("%d ", rootRecvData[i]);
        }

        printf("\n");
    }

    free(recvData);

    if (rank == 0) {
        free(data);
    }

    MPI_Finalize();

    return 0;
}
