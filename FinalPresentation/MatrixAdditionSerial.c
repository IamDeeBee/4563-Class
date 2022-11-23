//*************************************************************
// 
// Name: Nodebechukwu Okoye
//***************************************************************
// File:     MatrixAdditionSerial.c
// Purpose:  
//           
//           
//
// Input:
// Output:  
//
// Compile: gcc MatrixAdditionSerial.c -o MatrixAdditionSerialEXE.exe
//					./MatrixAdditionSerialEXE.exe row col
//
//					row:- row of the array
//					col:- col of the array
//
//*****************************************************************
//*******************************************************************

#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdlib.h>

int main(int argc, char **argv){
	//size of the array
	int row = atoi(argv[1]);
	int col = atoi(argv[2]);

	//Timing the code
	clock_t t;

	unsigned long long int final_sum=0;
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
  

  t = clock();

  //Local Summation
  for(int i =0; i < row; i++ ){
    for(int j =0; j < col; j++ ){
      local_Sum[i][j] = A[i][j] + B[i][j];
    }
    
  }

  t = clock() - t;

  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

  //Total Summation
  for(int i =0; i < row; i++ ){
    for(int j =0; j < col; j++ ){
      final_sum +=local_Sum[i][j];
    }
    
  }

  printf("Total sum : %lld\n", final_sum);
  printf("Total time %f seconds\n", time_taken);

  return 0; 

}