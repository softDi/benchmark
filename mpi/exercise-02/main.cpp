// PI Calculation 
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"
#include <math.h>

int main( int argc, char *argv[]){
    int done = 0, n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;

    if(argc<2){
        printf("Usage : ./Exercise intervalsToComputePi\n");
        return -1;
    }

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    if (myid == 0) {
        n = atoi(argv[1]);
        if (n == 0){
            printf("intervals cannot be zero\n");
            return -1;
        }
    }

    while (!done)
    {
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);  
        h   = 1.0 / (double) n;
        sum = 0.0;
        for (i = myid + 1; i <= n; i += numprocs) {
            x = h * ((double)i - 0.5);
            sum += 4.0 / (1.0 + x*x);
        }
        mypi = h * sum;

        MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
                MPI_COMM_WORLD);

        if (myid == 0){
            printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
            done = 1;               
        }
        MPI_Bcast(&done, 1, MPI_INT, 0, MPI_COMM_WORLD);     
    }
    MPI_Finalize();
    return 0;
}
