#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>
#include <omp.h>

using namespace std;
#define handle_error_en(en, msg) \
                   do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

       #define handle_error(msg) \
                   do { perror(msg); exit(EXIT_FAILURE); } while (0) } }
double **matrix_A;
double **matrix_B;
double **matrix_C;
static int matrix_dim;

class GridDim{
    public:
    int num_threads;
    int x;
    int y;
};

class ThreadId{
    public:
    int x;
    int y;
};


class ThreadInfo{
    public:
    pthread_t td;
    GridDim grid_dim;
    ThreadId tid;
    int dim;
};
//worker thread
void* matrix_multi(void* opaque)
{       
    ThreadInfo *tinfo = (ThreadInfo*)opaque;
    int block_x = matrix_dim / tinfo->grid_dim.x;
    int block_y = matrix_dim / tinfo->grid_dim.y;
    int i_begin = tinfo->tid.x * block_x;
    int j_begin = tinfo->tid.y * block_y;
    int i_end = ( tinfo->tid.x + 1 ) * block_x;
    int j_end = ( tinfo->tid.y + 1 ) * block_y;
    printf("Block[%d][%d]  \n", tinfo->tid.x, tinfo->tid.y);
    for(int i = i_begin; i < i_end; i++)
    {
        for(int j = j_begin; j < j_end; j++)
        {
            matrix_C[i][j] = 0;
            for(int k = 0; k < matrix_dim; k++)
            {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    GridDim grid_dim;
    if(argc<4){
        printf("This is a 2-D multi-thread matrix multiplication\n");
        printf("Usage: ./Exercise SquareMatrixDim GridDimX GridDimY \n");
        return 0;
    }
    else{
        matrix_dim = atoi(argv[1]);
        grid_dim.x = atoi(argv[2]);
        grid_dim.y = atoi(argv[3]);      
        grid_dim.num_threads = grid_dim.x * grid_dim.y ;
    }

    struct ThreadInfo *tinfo = (struct ThreadInfo *) malloc( grid_dim.num_threads * sizeof(struct ThreadInfo));
    pthread_attr_t thr_attr;
    pthread_attr_init(&thr_attr);

    matrix_A = (double**) malloc( matrix_dim*sizeof(double*) );
    matrix_B = (double**) malloc( matrix_dim*sizeof(double*) );
    matrix_C = (double**) malloc( matrix_dim*sizeof(double*) );
    for(int i = 0; i < matrix_dim; i++){
        matrix_A[i] = (double*) malloc( matrix_dim*sizeof(double) );
        matrix_B[i] = (double*) malloc( matrix_dim*sizeof(double) );
        matrix_C[i] = (double*) malloc( matrix_dim*sizeof(double) );
    }

    for(int i = 0; i < matrix_dim; i++){
        for(int j = 0; j < matrix_dim; j++){
            matrix_A[i][j] = i ;
            matrix_B[i][j] = j ;
        }
    }

    if( grid_dim.num_threads == 1 ){
        //#pragma omp parallel for 
        for(int i = 0; i < matrix_dim; i++){
            for(int j = 0; j < matrix_dim; j++){
                matrix_C[i][j] = 0;
                for(int k = 0; k < matrix_dim; k++){
                    matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
                }
            }
        }
    }
    else{
        for( int i = 0; i < grid_dim.num_threads; i++ ){
            tinfo[i].tid.x = i / grid_dim.y;
            tinfo[i].tid.y = i % grid_dim.y;
            tinfo[i].grid_dim = grid_dim;
            if( pthread_create( &tinfo[i].td, &thr_attr, matrix_multi, &tinfo[i]) != 0 ){
                printf ("Create pthread error!\n");
                exit (1);
            }
            else{
                printf("Thread-%d created.\n",tinfo[i].td);
            }
        }

        //joining the threads
        for(int i = 0; i < (grid_dim.x * grid_dim.y); i++){
            void *res;
            int s = pthread_join(tinfo[i].td, &res);
            if(s != 0){
                handle_error_en(s, "pthread_join");
            }else{
                printf("Thread-%d joined.\n",tinfo[i].td);
            }
        }
    }
   
   /* 
    for(int i = 0; i < matrix_dim; i++){
        free(matrix_A[i]);
        free(matrix_B[i]);
        free(matrix_C[i]);
    }
*/
    free(matrix_A);
    free(matrix_B);
    free(matrix_C);

    free(tinfo);
    return 0;
}


