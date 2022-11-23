//*************************************************************
// Example #1
// Name: Nodebechukwu Okoye
// Parallel Programming Date: Date of Submission N/A
//***************************************************************
// File:     BlockPartitionExample.c
// Purpose:  Use MPI to perform a block partition of an array of size 20
//           size 20 can be changed at any size as long as it is divisible by comm_sz
//	     THere are 4 participant processes.
//           
//           
//
// Input:    None.
// Output:   The data stored in each process   
//
// Compile:  
//  -Turing
//	  dos2unix BlockPartitionExampleScript
//  	qsub BlockPartitionExampleScript

//	-Stampede
//  	mpicc BlockPartitionExample.c -o BlockPartitionExampleEXE.exe
//		dos2unix BlockPartitionExampleScript
//		sbatch BlockPartitionExampleScript
//
//
// Algorithm:
//    1. Proces 0 fills up an array
//    2.  Each process get a portion via block partition
//    3. Print data stored in each process.
//
// Note:  The size of the array must be divisibl3 by the comm_sz
//
//
//*****************************************************************
//*******************************************************************

#include<stdio.h>
#include<mpi.h>
#include<malloc.h>
#include<stdlib.h>

//Prototypes
void fillArray(int *,int);


int main(int argc, char **argv){
	//For all participant processes
	int *orig_array, size;
	//For indiviual participant process
	int *local_array, local_size;
	//For MPI
	int rank,comm_sz;

	size=20;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

	local_size = size/comm_sz;
	local_array = (int *)malloc(local_size*sizeof(int));

	if(rank==0){
		//Allocate memory
		orig_array = (int *)malloc(size*sizeof(int));

		// Fill original array with values
		fillArray(orig_array,size);
	}

	//Scatter Data amongst indiviual process
	MPI_Scatter(orig_array,local_size,MPI_INT,local_array,local_size,MPI_INT,0,MPI_COMM_WORLD);


	printf("Data stored in Process %d \n",rank);
	for(int i = 0;i < local_size;i++){
		printf("%d ",local_array[i]);
	}
	printf("\n");

	// Clean up
  if (rank == 0) {
    free(orig_array);
  }
  free(local_array);
}

/*
Initializes original array

Parameter:
  int *data: pointer to array that will be initialized
  int SIZE: size of array
  
Returns:
  void
*/
void fillArray(int *data,int SIZE){
	int i;
  	for(i = 0; i < SIZE; i++){
    		data[i] = i+1;
  	}
}