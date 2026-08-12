#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int number1 = 6;
	int number2 = 3;
	int rank;
	int size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// If number of processes is not equal to 4 then abort
	if (size != 4) {
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	switch (rank) {
		// Perform addition operation
		case 0:
			printf("Process with rank %d has computed addition of %d and %d = %d.\n", rank, number1, number2, number1 + number2);
			break;

		// Perform subtraction operation
		case 1:
			printf("Process with rank %d has computed subtraction of %d and %d = %d.\n", rank, number1, number2, number1 - number2);
			break;

		// Perform multiplication operation
		case 2:
			printf("Process with rank %d has computed multiplication of %d and %d = %d.\n", rank, number1, number2, number1 * number2);
			break;

		// Perform division operation
		case 3:
			printf("Process with rank %d has computed division of %d and %d = %f.\n", rank, number1, number2, number1 / (number2 * 1.0));
			break;
	}

	MPI_Finalize();

	return 0;
}
