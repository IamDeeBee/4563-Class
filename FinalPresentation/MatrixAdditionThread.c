//*************************************************************
// 
// Name: Nodebechukwu Okoye
//***************************************************************
// File:     MatrixAdditionThread.c
// Purpose:  
//           
//           
//
// Input:
// Output:  
//
// Compile:
// 			Stampede2 
// 			gcc -fopenmp MatrixAdditionThread.c -o MatrixAdditionThreadEXE.exe
//			./MatrixAdditionThreadEXE.exe row col
//
//
// Algorithm:
//
// Note: 
//
//*****************************************************************
//*******************************************************************

#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char** argv){
    //size of the array
	int row = atoi(argv[1]);
	int col = atoi(argv[2]);

	unsigned long long int final_sum = 0;
	int A[row][col], B[row][col], local_Sum[row][col];



	//Fill Array
  int num = 1;
  for(int i =0; i < row; i++ ){
    for(int j =0; j < col; j++ ){
      A[i][j] = num;
      B[i][j] = num;
      num++;
    }  
  }

	double begin = omp_get_wtime();

  #pragma omp parallel for collapse(2) num_threads(16)
    for(int i =0; i < row; i++ ){
    	for(int j =0; j < col; j++ ){
      		local_Sum[i][j] =A[i][j] + B[i][j];
	   }
    }

  double wtime = omp_get_wtime()- begin;

  //Total Summation
  for(int i =0; i < (row); i++ ){
    for(int j =0; j < col; j++ ){
      final_sum +=local_Sum[i][j];
    }
    
  }
    
  printf("Total Sum: %d\n", final_sum);
  printf("Total Time: %f\n", wtime);

  return 0;
}