#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, d;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        d = 100;
        printf("Process 0 broadcasting data = %d\n", d);
        MPI_Bcast(&d, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(&d, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Process %d received data: %d\n", rank, d);
    }

    MPI_Finalize();
    return 0;
}