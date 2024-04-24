#include <iostream>
#include <chrono>
using namespace std;

// openmp: it is api which provids set of direcctives and EVs which enables parallel programming.
// #pragma omp parallel for shared(arr, swapped): This directive parallelizes the inner loop. It distributes the iterations of the loop among the available threads, allowing multiple threads to execute the loop iterations concurrently. The shared(arr, swapped) clause indicates that the arr and swapped variables are shared among all threads.
// : This pragma ensures that only one thread at a time executes the code within the critical section.

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

void bubble(int *arr, int n)
{
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void parBubb(int *arr, int n)
{
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
#pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
#pragma omp critical
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void print_list(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}

int main()
{
    int arr1[6] = {2, 5, 1, 3, 2, 4};
    int arr2[6] = {2, 5, 1, 3, 2, 4};
    int n = 6;
    auto s_s_time = chrono::high_resolution_clock::now();
    bubble(arr1, n);
    auto s_e_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> seqTim = s_e_time - s_s_time;
    cout << seqTim.count() << endl;

    auto s_p_t = chrono::high_resolution_clock::now();
    parBubb(arr2, n);
    auto e_p_t = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> parTim = e_p_t - s_p_t;
    cout << parTim.count() << endl;

    print_list(arr1, n);
    return 0;
}