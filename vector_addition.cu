!pip install git+https://github.com/afnan47/cuda.git

%load_ext nvcc_plugin

%%cu
#include <iostream>
using namespace std;
#include <cstdlib>

// CUDA kernel for vector addition
__global__ void vectorAdd(int *a, int *b, int *result, int n) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    if (tid < n) {
        result[tid] = a[tid] + b[tid];
    }
}

int main() {
    int *a, *b, *c;
    int *a_dev, *b_dev, *c_dev;
    int n = 5; // Example large number

    a = new int[n];
    b = new int[n];
    c = new int[n];
    int size = n * sizeof(int);

    cudaMalloc(&a_dev, size);
    cudaMalloc(&b_dev, size);
    cudaMalloc(&c_dev, size);

    // Initialize arrays with values
    for (int i = 0; i < n; i++) {
        a[i] = 1;
        b[i] = 2;
    }

    // Copy data from host to device
    cudaMemcpy(a_dev, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(b_dev, b, size, cudaMemcpyHostToDevice);

    int threads = 1024;
    int blocks = (n + threads - 1) / threads;

    // Execute kernel on GPU
    vectorAdd<<<blocks, threads>>>(a_dev, b_dev, c_dev, n);

    // Copy result back to host
    cudaMemcpy(c, c_dev, size, cudaMemcpyDeviceToHost);

    // Verify the result
    bool success = true;
    for (int i = 0; i < n; i++) {
        cout<<c[i]<<" ";
        if (c[i] != a[i] + b[i]) {
            success = false;
            std::cout << "Error at position " << i << std::endl;
            break;
        }
    }

    if (success) {
        std::cout << "Vector addition successful!" << std::endl;
    }

    // Free memory
    cudaFree(a_dev);
    cudaFree(b_dev);
    cudaFree(c_dev);
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

// host memeory: Host memory refers to the memory that is accessible by the CPU (host).
// device memory: Host memory refers to the memory that is accessible by the GPU or device
// threads: Threads are the smallest unit of execution in CUDA. Each thread executes a portion of the overall task independently.
// Threads are organized into groups called blocks that can execute concurrently on multiprocessors.
// nvcc plugin allows to compile and execute CUDA code directly within the notebook. 
// CUDA, which stands for Compute Unified Device Architecture, is a parallel computing platform and programming model developed by NVIDIA. It allows developers to use NVIDIA GPUs (Graphics Processing Units) for general-purpose processing, typically to accelerate computations that can be parallelized.
// it supports c, c++ and fortran