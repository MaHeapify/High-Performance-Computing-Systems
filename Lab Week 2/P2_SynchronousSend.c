/* 
	Write a MPI program using synchronous send. The sender process sends a word to the receiver.
	The second process receives the word, toggles each letter of the word and sends it back to the first process.
	Both process use synchronous send operations.
*/ 

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int rank;
	int size;
	char message[] = "Hello";

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// If number of processes is not equal to 2 then abort
	if (size != 2) {
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	if (rank == 0) {
		/* 
			Synchronous send sends a message and blocks until application buffer of sending task is free for reuse and 
			the destination process has started to receive the message
		*/
		MPI_Ssend(&message, (int)strlen(message) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		printf("Process with rank %d sent message %s to process with rank 1.\n", rank, message);

		MPI_Recv(&message, (int)strlen(message) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process with rank %d received the toggled message %s from process with rank 1.\n", rank, message);
	}
	else if (rank == 1) {
		MPI_Recv(&message, (int)strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process with rank %d received the message %s from process with rank 0.\n", rank, message);

		// Toggle the letters of the message using XOR operation
		for (int i = 0; i < (int)strlen(message); i++) {
			message[i] ^= 32;
		}

		MPI_Ssend(&message, (int)strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		printf("Process with rank %d toggled and sent message %s to process with rank 0.\n", rank, message);
	}

	MPI_Finalize();

	return 0;
}
