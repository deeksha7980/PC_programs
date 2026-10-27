
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX 100000

void merge(int arr[], int low, int mid, int high) {
    int i = low, j = mid + 1, k = low,temp[MAX];

    while (i <= mid && j <= high)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= high) temp[k++] = arr[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        arr[i] = temp[k];
}

void sequentialMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }

        merge(arr, low, mid, high);
    }
}

int main() {
    int n, i, a[MAX], b[MAX];
    double start, end;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Maximum size allowed is %d\n", MAX);
        return 0;
    }

    srand(time(NULL));

    for (i = 0; i < n; i++)
        a[i] = b[i] = rand() % 100000;

    start = omp_get_wtime();
    sequentialMergeSort(a, 0, n - 1);
    end = omp_get_wtime();
    printf("Sequential Merge Sort time: %f seconds\n", end - start);

    start = omp_get_wtime();
    parallelMergeSort(b, 0, n - 1);
    end = omp_get_wtime();
    printf("Parallel Merge Sort time: %f seconds\n", end - start);

    return 0;
}
