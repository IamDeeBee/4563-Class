//*************************************************************
// 
// Name: Nodebechukwu Okoye
//***************************************************************
// File:     HellowWorldOpenMP.c
// Purpose:  Basic HelloWorld for OpenMP 
//           using private variables
//           
//
// Input:
// Output:  
//
// Compile:
//			Stampede2 
// 			gcc -fopenmp HelloWorldOpenMP.c -o HelloWorldOpenMPEXE.exe
//			sbatch HelloWorldOpenMPScript
// Algorithm:
//
// Note: 
//
//*****************************************************************
//*******************************************************************

#include<stdio.h>
#include<omp.h>

int main(){
	int thread_id;

	#pragma omp parallel private(thread_id)
	{
		thread_id = omp_get_thread_num();
		printf("Hello from process: %d\n", thread_id);
	}
	return 0;
}