#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, re;
    int send_data[8], recv_data, gathered[8];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    

    if (rank == 0) {
        for (int i = 0; i < 8; i++)
            send_data[i] = i + 1;

        printf("Original Data: ");
        for (int i = 0; i < 8; i++)
            printf("%d ", send_data[i]);
        printf("\n");
    }

    MPI_Scatter(send_data, 1, MPI_INT, &recv_data, 1,
                MPI_INT, 0, MPI_COMM_WORLD);

    re = recv_data * recv_data;

    printf("Process %d received and squared: %d\n",
           rank, recv_data);

    MPI_Gather(&re, 1, MPI_INT, gathered, 1,
               MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered results (squares): ");
        for (int i = 0; i < 8; i++)
            printf("%d ", gathered[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}