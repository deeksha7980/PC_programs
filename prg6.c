
#include <stdio.h>
#include <mpi.h>

#define DEADLOCK_PART 2

int main(int argc, char *argv[]) {
    int r, s, n = 123;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    if (s < 2) {
        if (r == 0)
            printf("Run at least 2 processes\n");

        MPI_Finalize();
        return 0;
    }

#if DEADLOCK_PART == 2

    if (r == 0) {
        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        printf("Process 0 received back number: %d\n", n);
    }
    else if (r == 1) {
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        MPI_Send(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        printf("Process 1 received and sent back number: %d\n", n);
    }

#elif DEADLOCK_PART == 1

    if (r == 0) {
        printf("Process 0 waiting to receive from Process 1...\n");

        MPI_Recv(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (r == 1) {
        printf("Process 1 waiting to receive from Process 0...\n");

        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        MPI_Send(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

#endif

    MPI_Finalize();
    return 0;
}
