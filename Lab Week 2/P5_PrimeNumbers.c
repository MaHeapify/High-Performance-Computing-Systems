// Write a MPI program to find the prime numbers between 1 and 100 using two processes.

#include <mpi.h>
#include <stdio.h>
#include <math.h>

void checkPrime(int number, int rank) {
	for (int i = 2; i <= sqrt(number); i++) {
		if (number % i == 0) {
			return;
		}
	}

	printf("%d ", number);
}

int main(int argc, char* argv[]) {
	int rank;
	int size;
	int lower = 1;
	int upper = 100;
	int mid;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// If number of processes is not equal to 2 then abort
	if (size != 2) {
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	if (rank == 0) {
		mid = (lower + upper) / 2;

		printf("Prime numbers discovered by process with rank %d between %d - %d: ", rank, lower, mid - 1);

		// Figure out the prime numbers between 1 - 49
		for (int i = lower; i < mid; i++) {
			checkPrime(i, rank);
		}

		MPI_Send(&mid, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else if (rank == 1) {
		MPI_Recv(&mid, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		printf("Prime numbers discovered by process with rank %d between %d - %d: ", rank, mid, upper);

		// Figure out the prime numbers between 50 - 100
		for (int i = mid; i <= upper; i++) {
			checkPrime(i, rank);
		}
	}

	printf("\n");

	MPI_Finalize();

	return 0;
}
