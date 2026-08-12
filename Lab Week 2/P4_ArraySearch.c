#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void search(int data[], int dataLength, int key, int rank) {
	int found = 0;
	int index;

	for (int i = 0; i < dataLength; i++) {
		if (data[i] == key) {
			found = 1;
			index = i;
			break;
		}
	}

	if (found) {
		printf("Process with rank %d found the key %d at index %d in the array.\n", rank, key, index);
	}
	else {
		printf("Process with rank %d couldn't find the key %d in the array.\n", rank, key);
	}
}

int main(int argc, char* argv[]) {
	int rank;
	int size;
	int data[] = { 12, 56, 77, 20, 99 };
	int dataLength = sizeof(data) / sizeof(int);
	int key;

	// Buffer for Bsend
	// Size in bytes
	int bsize = 1000;
	void* bbuffer = malloc(bsize);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// If number of processes is not equal to 2 then abort
	if (size != 2) {
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	if (rank == 0) {
		printf("The array elements are: ");
		for (int i = 0; i < dataLength; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

		key = 71;

		search(data, dataLength, key, rank);

		MPI_Recv(&key, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		search(data, dataLength, key, rank);
	}
	else if (rank == 1) {
		key = 24;

		// Attach buffer before using MPI_Bsend
		MPI_Buffer_attach(bbuffer, bsize);

		MPI_Bsend(&key, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

		// Detach buffer after sending
		MPI_Buffer_detach(bbuffer, &bsize);
	}

	MPI_Finalize();

	return 0;
}
