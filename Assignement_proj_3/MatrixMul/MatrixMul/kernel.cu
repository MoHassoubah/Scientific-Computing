
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define  MAX_NUM_OF_ROWS 1000
#define	 MAX_NUM_OF_COLS 1000

float Matrix_1[MAX_NUM_OF_ROWS][MAX_NUM_OF_COLS];
float Matrix_2[MAX_NUM_OF_ROWS][MAX_NUM_OF_COLS];
float Matrix_output[MAX_NUM_OF_ROWS][MAX_NUM_OF_COLS];

int no_of_rows_1 = 64;
int no_of_rows_2 = 64;
int	no_of_cols_1 = 64;
int	no_of_cols_2 = 64;

void ReadMatrix_1_2(void);
cudaError_t MultiplyWithCuda(void);

__global__ void MultiplyKernel(int *c, const int *a, const int *b)
{
    
}

int main()
{
   
	// read 2 Matrix from Files
	ReadMatrix_1_2();
	// take time snap before multiplication
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//CPU Multiplication MAtrix_1 * Matrix_2
    cudaError_t cudaStatus = MultiplyWithCuda();
	// take time snap after multiplication
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }
	
	// print the Time taken to Multiply two Matrices 
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Multiplication Time CPU(us):" << duration << "\n";

	//print the output matrix for testing
//	for (int i = 0; i < no_of_cols_1; i++) {
//		for (int j = 0; j < no_of_rows_2; j++)
//		{
//			cout << Matrix_output[i][j] << "	";
//		}
//		cout << "\n";
//	}

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

    return 0;
}

// this function read the two matrices from two files with the dimensions given in the global variables set at the begining of the file
void ReadMatrix_1_2(void) {
	int x, y;
	ifstream in_1("Matrix_1.txt", std::ifstream::in);
	ifstream in_2("Matrix_2.txt", std::ifstream::in);

	if (!in_1 || !in_2) {
		cout << "Error! Cannot open file.\n";
		return;
	}
	else if (no_of_cols_1 != no_of_rows_2) {
		cout << "Error! Matrix dimensions is not valid for multiplication.\n";
		return;
	}

	for (y = 0; y < no_of_cols_1; y++) {
		for (x = 0; x < no_of_rows_1; x++) {
			in_1 >> Matrix_1[x][y];
		}
	}
	for (y = 0; y < no_of_cols_2; y++) {
		for (x = 0; x < no_of_rows_2; x++) {
			in_2 >> Matrix_2[x][y];
		}
	}

	in_1.close();
	in_2.close();
}


// Helper function for using CUDA to add vectors in parallel.
cudaError_t MultiplyWithCuda()
{
    int *dev_a = 0; //Matrix_1
    int *dev_b = 0; //Matrix_2
    int *dev_c = 0; //Matrix_output
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_c, no_of_rows_1*no_of_cols_2* sizeof(float));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_a, no_of_rows_1*no_of_cols_1 * sizeof(float));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_b, no_of_rows_2*no_of_cols_2 * sizeof(float));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_a, Matrix_1, no_of_rows_1*no_of_cols_1 * sizeof(float), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_b, Matrix_2, no_of_rows_2*no_of_cols_2 * sizeof(float), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
	MultiplyKernel <<<1, 5 >>>(dev_c, dev_a, dev_b);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(Matrix_output, dev_c, no_of_rows_1*no_of_cols_2 * sizeof(float), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

Error:
    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);
    
    return cudaStatus;
}
