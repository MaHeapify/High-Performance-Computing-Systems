#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank;
    int size;
    char word[] = "Hello";
    char originalLetter;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Figure out the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // If number of processes is not equal to 5 then abort
	if (size != 5) {
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

    originalLetter = word[rank];

    word[rank] ^= 32;

    printf("Process with rank %d toggled %c to %c.", rank, originalLetter, word[rank]);

    MPI_Finalize();

    return 0;
}
