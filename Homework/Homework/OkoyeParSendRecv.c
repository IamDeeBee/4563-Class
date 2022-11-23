//*************************************************************
// Assignment #2
// Name: Nodebechukwu Okoye
// Parallel Programming Date: Date of Submission (03/19/2022)
//***************************************************************
// File:     OkoyeParSendRecv.c
// Purpose: Use MPI_Send and MPI_Recv to send data from P0 to Pn 
//          (i.e n is number) in a round trip manner  
//
// Input:  N/A  
// Output:   OkoyeParSendRecv.o%j
//
// Compile:  mpicc OkoyeParSendRecv.c -o OkoyeParSendRecvEXE.exe
//
// Submit:   dos2unix OkoyeParSendRecvScript
//           sbatch OkoyeParSendRecvScript
// 
//
//
//
//
// 
//
//
//*****************************************************************
//*******************************************************************

#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */ 

const int MAX_STRING = 1024;

int main(void){
   char       greeting[MAX_STRING];  /* String storing message */
   int        comm_sz;               /* Number of processes    */
   int        my_rank;               /* My process rank        */
   int        q;
   int count;
   double start,stop;

   /* Start up MPI */
   MPI_Init(NULL, NULL); 

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 


   for(count=1;count<=10; count++){
      if(my_rank==0){
         /* Create message */
         sprintf(greeting, "Greetings");

         for (q = 1; q < comm_sz; q++){
            //Start Timer
            start = MPI_Wtime();

            /* Send message to process q */
            MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, q, 0,MPI_COMM_WORLD); 
            /* Receive message from process q */
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            //stop Timer
            stop = MPI_Wtime();
            
            printf("Round trip %d :Process 0 sent and received a message from Process %d in %f senconds \n",count, q , stop-start);
         }
      printf("\n"); 
      } 
      else{
        /*Receive a message from Process 0*/
        MPI_Recv(greeting, MAX_STRING, MPI_CHAR, 0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        /*Send Message back to Process 0*/
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0,MPI_COMM_WORLD);
      }

   }
   

   /* Shut down MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */