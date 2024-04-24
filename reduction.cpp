#include <iostream>
#include <omp.h>
using namespace std;

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