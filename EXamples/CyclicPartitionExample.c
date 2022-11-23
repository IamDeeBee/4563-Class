//*************************************************************
// Example #1
// Name: Nodebechukwu Okoye
// Parallel Programming Date: Date of Submission N/A
//***************************************************************
// File:     CyclicPartitionExample.c
// Purpose:  Use MPI to perform a Cyclic partition of an array of size 20
 //          size 20 can be changed at any size as long as it is divisible by comm_sz
//           
//           
//
// Input:    None.
// Output:   The data stored in each process   
//
// Compile:  
//  -Turing
//	  dos2unix CyclicPartitionExampleScript
//  	qsub CyclicPartitionExampleScript

//	-Stampede
//  	mpicc CyclicPartitionExample.c -o CyclicPartitionExampleEXE.exe
//		dos2unix CyclicPartitionExampleScript
//		sbatch CyclicPartitionExampleScript
//
//
// Algorithm:
//
// Note:  The size of the array must be divisible by the comm_sz
//
//
//*****************************************************************
//*******************************************************************

#include<stdio.h>
#include<mpi.h>
#include<malloc.h>
#include<stdlib.h>

//Prototype
void fillArray(int *,int);
void rearrangeArray(int *,int ,int*,int,int);


int main(int argc, char **argv){
	//For all participant processes
	int *orig_array, *cyclic_array, size;
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

	int temp_store;

	if(rank==0){
		//Allocate memory
		orig_array = (int *)malloc(size*sizeof(int));
		cyclic_array = (int *)malloc(size*sizeof(int));

		// Fill original array with values
		fillArray(orig_array,size);

		//rearrange original array into cyclic manner and delete original array
		rearrangeArray(orig_array,size,cyclic_array,local_size,comm_sz);
		free(orig_array);
	}

	//Scatter Data amongst indiviual process
	MPI_Scatter(cyclic_array,local_size,MPI_INT,local_array,local_size,MPI_INT,0,MPI_COMM_WORLD);

	printf("\n");
	printf("Data stored in Process %d \n",rank);
	for(int i = 0;i < local_size;i++){
		printf("%d ",local_array[i]);
	}
	printf("\n");

	// Clean up
  if (rank == 0) {
    free(cyclic_array);
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

/*
Rearranges original array in a cyclic way

Parameter:
  int *old_array: pointer to array that will be rearranged
  int size: size of array
  int *new_array: pointer to array that will store the rearranged old array
  int subsize: used to rearrange the array
  int comm_sz: number of processes
  
Returns:
  void
*/
void rearrangeArray(int *old_array,int size,int *new_array,int subsize,int commsz){
	int j = 0;
  int k = 0;
  printf("Cyclic Array\n");
  for(int i = 0; i < size; i++){
    new_array[i] = old_array[j];
    j = j + commsz;
    
    if((i+1)%subsize==0){
      k = k + 1;
      j = k;
    }
  }

}