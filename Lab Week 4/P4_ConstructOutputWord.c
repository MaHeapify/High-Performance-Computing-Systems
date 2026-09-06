/*
    Write a MPI program to read a word of length N. Using N processes including the root 
    get output word with the pattern as shown in the example. Display the resultant output word 
    in the root. Calculate the amount of time taken by each process and the whole program.

    Eg: Input: PCAP     Output: PCCAAAPPPP
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char word[] = "PCAP";
    int length = strlen(word);
    int totalOutputLength = (length*(length + 1))/2 + 1;
    char outputWord[totalOutputLength];
    char subwords[length + 1];
    int rank;
    int sumRank = 0;
    int size;
    int contribution;
    double start;
    double end;
    double localTime;
    double totalStart;
    double totalEnd;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != length) {
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    // Start time of the whole program
    MPI_Barrier(MPI_COMM_WORLD);
    totalStart = MPI_Wtime();

    // Start time for this process
    start = MPI_Wtime();

    int recvCounts[size];
    int displacements[size];

    contribution = rank + 1;
    MPI_Scan(&contribution, &sumRank, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    
    int myDisplacement = sumRank - contribution;

    for (int i = 0; i < contribution; i++) {
        subwords[i] = word[rank];
    }
    subwords[contribution] = '\0';

    // Gathers the number of characters contributed by each process
    MPI_Gather(&contribution, 1, MPI_INT, recvCounts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Gathers all the displacement values required for the contruction of the final word
    MPI_Gather(&myDisplacement, 1, MPI_INT, displacements, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Gatherv allows each process to send back different lengths of data in order to be combined by the root later
    MPI_Gatherv(subwords, contribution, MPI_CHAR, outputWord, recvCounts, displacements, MPI_CHAR, 0, MPI_COMM_WORLD);

    // End time for this process
    end = MPI_Wtime();
    localTime = end - start;

    printf("The process with rank %d has generated the string %s in time = %f seconds.\n", rank, subwords, localTime);

    // Make sure all processes have finished
    MPI_Barrier(MPI_COMM_WORLD);

    totalEnd = MPI_Wtime();

    if (rank == 0) {
        outputWord[totalOutputLength - 1] = '\0';
        printf("\nInput word: %s", word);
        printf("\nOutput word: %s\n", outputWord);
        printf("\nTotal program time = %f seconds.\n", totalEnd - totalStart);
    }

    MPI_Finalize();

    return 0;
}
