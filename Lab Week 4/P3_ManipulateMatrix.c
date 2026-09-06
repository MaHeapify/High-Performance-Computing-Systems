/*
    Write a MPI program to read 4x4 matrix and display the following output using four processes.

    Input matrix:       Output matrix:
    1 2 3 4             1 2 3 4
    1 2 3 1             2 4 6 5
    1 1 1 1             3 5 7 6
    2 1 2 1             5 6 9 7

*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int row[4];
    int outputRow[4];
    int inputMatrix[4][4] = {
        {1, 2, 3, 4},
        {1, 2, 3, 1},
        {1, 1, 1, 1},
        {2, 1, 2, 1}
    };
    int outputMatrix[4][4];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size != 4) {
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    // Send one row from the input matrix to each process
    MPI_Scatter(inputMatrix, size, MPI_INT, row, size, MPI_INT, 0, MPI_COMM_WORLD);

    // Add subsequent rows to get the desired output matrix
    MPI_Scan(row, outputRow, size, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Gather the final resultant rows in the output matrix
    MPI_Gather(outputRow, size, MPI_INT, outputMatrix, size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nInput matrix:\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%d ", inputMatrix[i][j]);
            }
            printf("\n");
        }

        printf("\nOutput matrix:\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%d ", outputMatrix[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    
    return 0;
}
