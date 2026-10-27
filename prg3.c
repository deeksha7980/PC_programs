
#include <stdio.h>
#include <omp.h>

int fib(int n) {
    if (n <= 1)
        return n;

    int x, y;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n, result;
    double start, end;

    printf("Enter value of n: ");
    scanf("%d", &n);

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }

    end = omp_get_wtime();

    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Execution Time: %f seconds\n", end - start);

    return 0;
}
