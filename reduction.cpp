#include <iostream>
#include <omp.h>
using namespace std;

// Parallel reduction is a technique used in parallel computing to combine the results of individual computations performed by multiple
// threads into a single result. It's commonly used in scenarios where each thread performs a computation on a portion of data, and the
// final result is a combination of these partial results.
// reduction(max : max): This clause specifies that a reduction operation should be performed on the variable max using the max operation.
// It ensures that each thread has its own private copy of max, and at the end of the parallel region, all private copies are combined
// using the max operation to compute the final value of max.

void maxelem(int *arr, int n)
{
    int max = -9999999;
#pragma omp parallel for reduction(max : max)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    cout << "max is: " << max << endl;
}

void minelem(int *arr, int n)
{
    int min = 9999999;
#pragma omp parallel for reduction(min : min)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }
    cout << "min is: " << min << endl;
}

void sumelem(int *arr, int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "sum is: " << sum << endl;
}

void avgelem(int *arr, int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "avg is: " << double(sum) / (n) << endl;
}

int main()
{
    int arr[5] = {2, 1, 3, 5, 4};
    int n = 5;
    maxelem(arr, n);
    minelem(arr, n);
    sumelem(arr, n);
    avgelem(arr, n);
    return 0;
}