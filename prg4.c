
#include <stdio.h>
#include <omp.h>
#include <time.h>

int is_prime(int n) {
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main() {
    int n = 10000000;
    clock_t s, e;
    double cpu_time;

    printf("The range of numbers is 1 to %d\n\n", n);

    s = clock();

    for (int i = 1; i <= n; i++)
        is_prime(i);

    e = clock();
    cpu_time = (double)(e - s) / CLOCKS_PER_SEC;

    printf("Time to compute prime numbers serially: %f seconds\n",
           cpu_time);

    s = clock();

    #pragma omp parallel for
    for (int i = 1; i <= n; i++)
        is_prime(i);

    e = clock();
    cpu_time = (double)(e - s) / CLOCKS_PER_SEC;

    printf("Time to compute prime numbers in parallel: %f seconds\n",
           cpu_time);

    return 0;
}
