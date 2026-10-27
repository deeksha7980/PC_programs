
#include <stdio.h>
#include <omp.h>

int main() {
    int n, thread;

    printf("Enter no of tasks: ");
    scanf("%d", &n);

    printf("Enter no of threads: ");
    scanf("%d", &thread);

    omp_set_num_threads(thread);

    printf("\n");

    #pragma omp parallel for schedule(static, 2)
    for (int i = 0; i < n; i++) {
        printf("Thread %d executes iteration %d\n",
               omp_get_thread_num(), i);
    }

    return 0;
}
