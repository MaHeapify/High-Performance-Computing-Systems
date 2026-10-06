/*
    Write an OpenMP program that reads a matrix, finds the maximum element in each row 
    and the maximum element in each column, and displays them. Use parallel for loops and show 
    the output for a sample 4x4 matrix.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int matSize = 4;
    int mat[matSize][matSize];

    // Populate the 4x4 matrix with random numbers
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matSize; j++) {
            int randomNumber = rand() % 10;

            mat[i][j] = randomNumber;
        }
    }

    // Display the populated matrix
    printf("\nInput matrix:\n\n");
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matSize; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    // Find out the max element in each row
    printf("\nRow maximums:");

    #pragma omp parallel for
    for (int i = 0; i < matSize; i++) {
        int rowMax = mat[i][0];
        for (int j = 1; j < matSize; j++) {
            if (mat[i][j] > rowMax) {
                rowMax = mat[i][j];
            }
        }
        printf("\nMax element in row %d: %d", i + 1, rowMax);
    }
    printf("\n");

    // Find out the max element in each column
    printf("\nColumn maximums:");

    #pragma omp parallel for
    for (int j = 0; j < matSize; j++) {
        int colMax = mat[0][j];
        for (int i = 1; i < matSize; i++) {
            if (mat[i][j] > colMax) {
                colMax = mat[i][j];
            }
        }
        printf("\nMax element in column %d: %d", j + 1, colMax);
    }
    printf("\n");

    return 0;
}
