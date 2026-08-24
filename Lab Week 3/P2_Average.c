/*
    Write a MPI program to read a value M and N x M elements in the root process. Root 
    process sends M elements to each process. Each process finds average of M elements it received 
    and sends these average values to root. Root collects all the values and finds the total average. Use N 
    number of processes.
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float calculateAverage(int recvData[], int value) {
    int sum = 0;

    for (int i = 0; i < value; i++) {
        sum += recvData[i];
    }

    return (sum / (float)value);
}

int main(int argc, char *argv[]) {
    int rank;
    int size;
    int numberOfElements;
    int *data;
    int *recvData;
    float average;
    float totalAverage = 0.0f;
    int value;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    float rootRecvData[size];
    
    if (size <= 2) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    if (rank == 0) {
        srand(time(NULL));

        // Generate a random number in the range of 1 - 9
        value = rand() % 9 + 1;

        numberOfElements = size * value;
        
        data = malloc(numberOfElements * sizeof(int));
        
        for (int i = 0; i < numberOfElements; i++) {
            data[i] = rand() % 10;
        }
    }
    
    // Broadcasts a message from the root process to all other processes
    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    recvData = malloc(value * sizeof(int));

    MPI_Scatter(data, value, MPI_INT, recvData, value, MPI_INT, 0, MPI_COMM_WORLD);

    average = calculateAverage(recvData, value);

    printf("The process with rank %d has received %d values from the process with rank 0 and has computed the average: %f", rank, value, average);    

    // The root process collects data from all other processes
    MPI_Gather(&average, 1, MPI_FLOAT, rootRecvData, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\n\nThe process with rank 0 has gathered the following average values from each of the processes:\n");
        for (int i = 0; i < size; i++) {
            totalAverage += rootRecvData[i];
            printf("%f\n", rootRecvData[i]);
        }

        printf("\nThe total average calculated by the root upon receiving the averages from each of the processes: %f\n", totalAverage);
    }

    free(recvData);

    if (rank == 0) {
        free(data);
    }

    MPI_Finalize();

    return 0;
}
