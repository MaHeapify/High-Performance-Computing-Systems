/*
    Write a MPI program to read two strings S1 and S2 of same length in the root process. 
    Using N process including the root (string length is evenly divisible by N), produce the concatenated 
    resultant string as shown below. Display the resultant string in the root process.

    Eg: String S1: string       String S2: length       Resultant String: slternigntgh
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int length = 6;
    char string1[] = "string";
    char string2[] = "length";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (length % size != 0) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Figure out the number of items to be scattered per process
    int local = length / size;

    char recv1[local];
    char recv2[local];
    char localResult[local * 2 + 1];
    char finalResult[length * 2 + 1];

    MPI_Scatter(string1, local, MPI_CHAR, recv1, local, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(string2, local, MPI_CHAR, recv2, local, MPI_CHAR, 0, MPI_COMM_WORLD);

    int j = 0;

    // Interleave the characters from the two strings to build the resultant string
    for (int i = 0; i < local; i++) {
        localResult[j++] = recv1[i];
        localResult[j++] = recv2[i];
    }

    // Append NULL terminating character at the end
    localResult[j] = '\0';

    MPI_Gather(localResult, local * 2, MPI_CHAR, finalResult, local * 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        finalResult[length * 2] = '\0';

        printf("Resultant string is: %s\n", finalResult);
    }
    
    MPI_Finalize();

    return 0;
}
