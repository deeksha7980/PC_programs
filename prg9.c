#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
    int r, v, sum, max;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &v);
    v= r + 1;
    MPI_Reduce(&v, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (r == 0)
        printf("Sum using Reduce: %d\n", sum);
    MPI_Allreduce(&v, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    printf("Max using Allreduce (rank %d): %d\n", r, max);
    MPI_Finalize();
    return 0;
}