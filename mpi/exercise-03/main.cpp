/******************************************************************************
* FILE: mpi_mm.c
* DESCRIPTION:  
*   MPI Matrix Multiply - C Version
*   In this code, the master task distributes a matrix multiply
*   operation to numtasks-1 worker tasks.
*   NOTE:  C and Fortran versions of this code differ because of the way
*   arrays are stored/passed.  C arrays are row-major order but Fortran
*   arrays are column-major order.
* AUTHOR: Blaise Barney. Adapted from Ros Leibensperger, Cornell Theory
*   Center. Converted to MPI: George L. Gusciora, MHPCC (1/95)
* LAST REVISED: 04/13/05
******************************************************************************/

// Fix me : from ltrace result, " Error in `./Exercise': free(): invalid next size (fast): 0x00000000014e1690 *** ", I thought it was caused by hydra  


#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MASTER 0               /* taskid of first task */
#define FROM_MASTER 1          /* setting a message type */
#define FROM_WORKER 2          /* setting a message type */

double *matrix_alloc(uint32_t rows, uint32_t cols, double inival){
    double *matrix = (double *)malloc(rows*cols*sizeof(double));
    for (int i=0; i<rows*cols; i++){
            matrix[i]=inival;
    }
    return matrix;
}


int main (int argc, char *argv[])
{
    int	numtasks,              /* number of tasks in partition */
	    taskid,                /* a task identifier */
	    numworkers,            /* number of worker tasks */
	    source,                /* task id of message source */
	    dest,                  /* task id of message destination */
	    mtype,                 /* message type */
	    rows,                  /* rows of matrix A sent to each worker */
	    averow, extra, offset, /* used to determine rows sent to each worker */
	    i, j, k, rc;           /* misc */
    double *a, *b, *c;

    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    if (numtasks < 2 ) {
        printf("Need at least two MPI tasks. Quitting...\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
        exit(1);
    }
    numworkers = numtasks-1;




    if(argc < 4){
        printf("Usage : ./Exercise rowsA colsA colsB\n");
    }
    uint32_t NRA=atoi(argv[1]);                 /* number of rows in matrix A */
    uint32_t NCA=atoi(argv[2]);                 /* number of columns in matrix A */
    uint32_t NCB=atoi(argv[3]);                  /* number of columns in matrix B */

    a = matrix_alloc(NRA,NCA,1);
    b = matrix_alloc(NCA,NCB,1);
    c = matrix_alloc(NRA,NCB,0);

/**************************** master task ************************************/
   if (taskid == MASTER)
   {

       printf("mpi_mm has started with %d tasks and %d workers\n", numtasks, numworkers);
      
      /* Send matrix data to the worker tasks */
      averow = NRA/numworkers;
      extra = NRA%numworkers;
      offset = 0;
      mtype = FROM_MASTER;
      for (dest=1; dest<=numworkers; dest++)
      {
         rows = (dest <= extra) ? averow+1 : averow;   	
         printf("Sending %d rows to task %d offset=%d\n",rows,dest,offset);
         MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&a[offset*NCA], rows*NCA, MPI_DOUBLE, dest, mtype,
                   MPI_COMM_WORLD);
         MPI_Send(b, NCA*NCB, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
         offset = offset + rows;
      }

      /* Receive results from worker tasks */
      mtype = FROM_WORKER;
      for (i=1; i<=numworkers; i++)
      {
         source = i;
         MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&c[offset*NCB], rows*NCB, MPI_DOUBLE, source, mtype, 
                  MPI_COMM_WORLD, &status);
         printf("Received results from task %d, matrix offset = %d\n", source, offset);
      }

      if( NRA*NCB <= 100 ){
          /* Print results */
        printf("******************************************************\n");
        printf("Result Matrix:\n");
        for (i=0; i<NRA; i++){
           printf("\n"); 
           for (j=0; j<NCB; j++) 
              printf("%6.2f   ", c[i*NCB+j]);
        }
        printf("\n******************************************************\n");
      }
      printf ("Done.(Only matrixes with its size less than 10*10 will be shown.)\n");
 
   }


/**************************** worker task ************************************/
   if (taskid > MASTER)
   {
      mtype = FROM_MASTER;
      MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(a, rows*NCA, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(b, NCA*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

      for (k=0; k<NCB; k++){
         for (i=0; i<rows; i++){
            c[i*NCB+k] = 0.0;
            for (j=0; j<NCA; j++)
               c[i*NCB+k] = c[i*NCB+k] + a[i*NCA+j] * b[j*NCB+k];
         }
      }
      mtype = FROM_WORKER;
      MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(c, rows*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
   }
         
    free(a);
    free(b);
    free(c);      
    MPI_Finalize();
}
