//*************************************************************
// 
// Name: Nodebechukwu Okoye
//***************************************************************
// File:     HellowWorldOpenMP.c
// Purpose:  Basic HelloWorld for OpenMP
//           
//           
//
// Input:
// Output:  
//
// Compile:
//			Stampede2 
// 			gcc -fopenmp HelloWorldOpenMP.c -o HelloWorldOpenMPEXE.exe
//
// Algorithm:
//
// Note: 
//
//*****************************************************************
//*******************************************************************

#include<stdio.h>
#include<omp.h>

int main(){
	#pragma omp parallel
	{
		printf("Hello from process: %d\n", omp_get_thread_num());
	}
	return 0;
}