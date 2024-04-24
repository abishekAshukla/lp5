#include <iostream>
#include <omp.h>
#include <chrono>
using namespace std;

// #pragma omp parallel sections: sections within the block will be executed parallely
// #pragma omp section: defines  asection to be executed by a thread

void merge(int *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int arr1[n1];
    int arr2[n2];

    for (int i = 0; i < n1; i++)
    {
        arr1[i] = arr[left + i];
    }

    for (int i = 0; i < n2; i++)
    {
        arr2[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (arr1[i] < arr2[j])
        {
            arr[k] = arr1[i];
            i++;
        }
        else
        {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = arr1[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}

void print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void mergeSortPar(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergeSortPar(arr, left, mid);
            }
#pragma omp section
            {
                mergeSortPar(arr, mid + 1, right);
            }
        }
        merge(arr, left, mid, right);
    }
}

void mergeSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{
    //   int arr[7] = {3, 2, 1, 2, 8, 5, 3};
    int n;
    cout << "enter size: " << endl;
    cin >> n;
    int *arr = new int[n];
    cout << "Enter elements: " << endl;
    int *arr1 = new int[n];
    int *arr2 = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr1[i];
        arr2[i] = arr1[i];
    }

    auto s_s_t = chrono::high_resolution_clock::now();
    mergeSort(arr2, 0, n - 1);
    auto s_e_t = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> s_t = s_e_t - s_s_t;
    cout << s_t.count() << endl;

    auto p_s_t = chrono::high_resolution_clock::now();
    mergeSortPar(arr2, 0, n - 1);
    auto p_e_t = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> p_t = p_e_t - p_s_t;
    cout << p_t.count() << endl;
    print(arr2, n);
    return 0;
}