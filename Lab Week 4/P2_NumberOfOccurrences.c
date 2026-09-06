/*
    Write a MPI program to read a 3x3 matrix. Enter an element to be searched in the root 
    process. Find the number of occurrences of this element in the matrix using three processes.
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Randomly populate the matrix with numbers from 0 to 9
void randomlyPopulateMatrixAndDisplay(int matrix[][3], int size) {
    printf("\nThe matrix is as follows:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Computes the count of occurrences of the element searched, per row
int countOccurrencesPerRowPerProcess(int row[], int size, int elementToSearch) {
    int countPerRow = 0;

    for (int i = 0; i < size; i++) {
        if (row[i] == elementToSearch) {
            countPerRow++;
        }
    }
    
    return countPerRow;
}

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int elementToSearch;
    int countPerRow = 0;
    int totalOccurrences = 0;

    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    int matrix[size][size];
    int row[size];
    
    if (rank == 0) {
        // Randomly select an element to search for
        elementToSearch = rand() % 10;

        printf("\nThe element to search for the number of occurrences is %d.\n", elementToSearch);

        randomlyPopulateMatrixAndDisplay(matrix, size);
    }

    MPI_Bcast(&elementToSearch, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Send one row from the input matrix to each process
    MPI_Scatter(matrix, size, MPI_INT, row, size, MPI_INT, 0, MPI_COMM_WORLD);

    countPerRow = countOccurrencesPerRowPerProcess(row, size, elementToSearch);

    // Root collects the data from all the other processes in the same communicator, and performs an operation on the data
    MPI_Reduce(&countPerRow, &totalOccurrences, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nThe number of occurrences of %d in the matrix is = %d.\n", elementToSearch, totalOccurrences);
    }

    MPI_Finalize();

    return 0;
}
