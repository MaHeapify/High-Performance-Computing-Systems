// Write a program in MPI where even ranked process prints "Hello" and odd ranked process prints "World".

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank % 2 == 0) {
        // Even ranked process prints Hello
        printf("Process with rank %d: Hello.", rank);
    } else {
        // Odd ranked process prints World
        printf("Process with rank %d: World.", rank);
    }

    MPI_Finalize();

    return 0;
}
