//*************************************************************
// Assignment #2
// Name: Nodebechukwu Okoye
// GPU Date: Date of Submission (9/20/2020)
/***************************************************************
// File:     ArrayMultiCUDA.cu
// Purpose:  Use CUDA to compute the product of two arrays and 
//			 store the product in another array
//           
//
// Input:    None.
// Output:   The product of the first and last elements of 
//			 the product array
//
// Compile:  
// 
//
//
// Algorithm:
//    1. Proces 0 initializes and scatters array amongst processes
//    2.  Each process calculates "its" portion of the FFT
//    3a. Each process != 0 sends their calculated FFT  to process 0.
//    3b. Process 0 receives the sum from other individual processes
//        stores in an array, sumsthe array   and prints the result.
//
//
//*****************************************************************
//*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

const int SIZE = 4096;

int main()
{
	printf("Hi\n");

	//Variable Decleration
	unsigned long long int *A_h;
	unsigned long long int *B_h;
	unsigned long long int *C_h;
	unsigned long long int *sum_h;



	//Memory Allocation
	A_h = (unsigned long long int *) malloc(SIZE * sizeof(unsigned long long int ));
	B_h = (unsigned long long int *) malloc(SIZE * sizeof(unsigned long long int ));
	C_h = (unsigned long long int *) malloc(SIZE * sizeof(unsigned long long int ));
	sum_h = (unsigned long long int *) malloc(sizeof(unsigned long long int ));


	//Fill Array
	for(int i=0; i<=SIZE; i++)
	{
		A_h[i]=i;
		B_h[i]=(SIZE-1)+i;
		C_h[i] = A_h[i] * B_h[i];
		sum_h +=C_h[i];
	}
	//View Array 
		printf("%llu\n",C_h[0]);
		printf("%llu\n",C_h[SIZE-1]);
		printf("%llu\n",sum_h);
}