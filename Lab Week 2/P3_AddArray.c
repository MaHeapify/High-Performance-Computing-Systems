#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int rank;
	int size;
	int firstPartSum = 0;
	int secondPartSum = 0;
	int data[] = {1, 2, 3, 4, 5, 6};
	int dataLength = sizeof(data) / sizeof(int);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// If number of processes is not equal to 2 then abort
	if (size != 2) {
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	if (rank == 0) {
		// Calculate the sum of first part of the array
		for (int i = 0; i < dataLength / 2; i++) {
			firstPartSum += data[i];
		}

		printf("Process with rank %d has computed the sum of first part of the array = %d.\n", rank, firstPartSum);

		MPI_Recv(&secondPartSum, dataLength / 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Sum of array of %d elements computed by process with rank 0 and 1 = %d.\n", dataLength, firstPartSum + secondPartSum);
	}
	else if (rank == 1) {
		// Calculate the sum of the second part of the array
		for (int i = dataLength / 2; i < dataLength; i++) {
			secondPartSum += data[i];
		}

		MPI_Send(&secondPartSum, dataLength / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("Process with rank %d has computed the sum of second part of the array = %d, and is sent to process with rank 0.\n", rank, secondPartSum);
	}

	MPI_Finalize();

	return 0;
}
