//*************************************************************
// Assignment #1
// Name: Nodebechukwu Okoye
// GPU Date: Date of Submission (9/25/2020)
/***************************************************************
// File:     NodebechukwuOkoyeA1.cu
// Purpose:  Use CUDA to compute the product of two arrays and 
//			 store the product in another array
//           
//
// Input:    None.
// Output:   the first and last elements of the product array
//
// Compile:  sbatch NodebechukwuOkoyeA1Script
// 
//
//
// Algorithm:
//    1. Declare variable for both the host(GPU) and device(CPU)
//    2. Allocate Memory to host(CPU) and device(GPU) via malloc and cudaMalloc
//    3. Populate the arrays
//    4. Copy the given data from host to device via cudaMemCpy
//    5. Define your grid and block dimensions
//    6. Call your Kernel function
//    7. In Kernel: Generate a unique Id for array Index
//    8.	    Perform the Needed calculations
//    9. Copy the solution from device to host via cudaMemCpy
//    10. Free allocated memory via cudaFree and free
//
//*****************************************************************
//*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

const int SIZE = 4096;


__global__
void arrayMulti(int size ,unsigned long long int *a, unsigned long long int *b, unsigned long long int *c)
{
 	int i = blockIdx.x * blockDim.x + threadIdx.x;
	
	if(i < size){
		c[i] = a[i] * b[i];
	}
	
 	
}
int main()
{
	//Variable Decleration
	 //For Host(CPU)
	unsigned long long int *A_h;
	unsigned long long int *B_h;
	unsigned long long int *C_h;
	unsigned long long int sum_h = 0;
	 //For Device(GPU)
	unsigned long long int *A_d;
	unsigned long long int *B_d;
	unsigned long long int *C_d;

	//size of memory to allocate on the device
	const int isize = SIZE*sizeof(unsigned long long int);

	//Memory Allocation
	 //for Host(CPU)
	A_h = (unsigned long long int *) malloc(SIZE * sizeof(unsigned long long int ));
	B_h = (unsigned long long int *) malloc(SIZE * sizeof(unsigned long long int ));
	C_h = (unsigned long long int *) malloc(SIZE * sizeof(unsigned long long int ));

	 //for Device(GPU)
	cudaMalloc( (void**)&A_d, isize);
 	cudaMalloc( (void**)&B_d, isize);
 	cudaMalloc( (void**)&C_d, isize);

	//Populate the Array
	for(int i=0; i<SIZE; i++)
	{
		A_h[i]=i;
		B_h[i]=(SIZE-1)+i;
	}

 	cudaMemcpy( A_d, A_h, isize, cudaMemcpyHostToDevice );
 	cudaMemcpy( B_d, B_h, isize, cudaMemcpyHostToDevice );


	int blockSize = 1024;
	int gridSize = (SIZE+blockSize)/blockSize;

	//Define the Block and Grid Dimension
	dim3 dimGrid(gridSize,1);
	dim3 dimBlock(blockSize,1);

	arrayMulti<<<dimGrid,dimBlock>>>(isize, A_d, B_d, C_d);

	cudaMemcpy( C_h, C_d, isize, cudaMemcpyDeviceToHost );
 	cudaFree( A_d );
	cudaFree( B_d );
	cudaFree( C_d );
	

	for(int i = 0; i < SIZE; i++ ){
		sum_h += C_h[i];
	}
	
	printf("The first product is %llu\n", C_h[0]);
	printf("The last product is %llu\n", C_h[SIZE-1]);
	printf("The sum of the whole array is %llu\n", sum_h);

	free( A_h );
	free( B_h);
	free( C_h );

 	return EXIT_SUCCESS;


}