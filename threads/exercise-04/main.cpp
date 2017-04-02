#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>
#include <omp.h>
#include <utmpx.h> // To get core-ID
#include <sched.h>   // To cpu_set_t , CPU_SET

using namespace std;
#define handle_error_en(en, msg) \
                   do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

       #define handle_error(msg) \
                   do { perror(msg); exit(EXIT_FAILURE); } while (0) } }
double *results;
static int n_points;
static int n_threads;
static bool enable_affinity=false;

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
void* pi_multi(void* opaque)
{       
    int seed;
    struct drand48_data drand_buf;
    srand48_r (seed, &drand_buf); 

    ThreadInfo *tinfo = (ThreadInfo*)opaque;
    cpu_set_t cpuset;
    int cpu = tinfo->tid.x;
    if(enable_affinity){
        CPU_ZERO(&cpuset);
        CPU_SET(cpu, &cpuset);
        pthread_t thread = pthread_self();
        int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);           
        if (s != 0){
            handle_error_en(s, "pthread_setaffinity_np");
        }
        /* Check the actual affinity mask assigned to the thread */
        s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
        if (s != 0){
            handle_error_en(s, "pthread_getaffinity_np"); 
        }
    }

    int batch_size = n_points / n_threads;
        printf("Inside thread-%d, batch_size=%d\n", tinfo->tid.x, batch_size);
    double pointsIn = 0;    

    for(int i = 0; i < batch_size; i++)
    {
        double x;
        double y; 
        drand48_r (&drand_buf, &x);
        drand48_r (&drand_buf, &y);
        double distance = (x * x) + (y * y); 
        distance = sqrt(distance); 
        if(distance <= 1){
            pointsIn++;
            //printf( "thread-%d  cpu-%d\n", tinfo->tid.x, sched_getcpu() ); 
        }
    } 
    results[tinfo->tid.x] = pointsIn ; 
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    double pi, pointsIn = 0, xValue, yValue, distance; 
    if(argc<3){
        printf("This is a multi-thread PI computation\n");
        printf("Usage: ./Exercise n_points n_threads  \n");
        return 0;
    }
    else{
        n_points = atoi(argv[1]);
        n_threads = atoi(argv[2]);
    }
    
    srand(time(0));

    results = (double*) malloc( n_threads*sizeof(double) );

    struct ThreadInfo *tinfo = (struct ThreadInfo *) malloc( n_threads * sizeof(struct ThreadInfo));
    pthread_attr_t thr_attr;
    pthread_attr_init(&thr_attr);

    if( n_threads == 999 ){
        printf("This is the no thread version\n");
        pointsIn = 0;
        //#pragma omp parallel for
        for(int i=0; i < n_points; i++){ 
            xValue = (double) rand()/RAND_MAX; //Random point: x 
            yValue = (double) rand()/RAND_MAX; //Random point: y
            distance = (xValue * xValue) + (yValue * yValue); 
            distance = sqrt(distance); 
            if(distance <= 1){
                pointsIn++; 
            }
        } 
        pi = 4 * pointsIn/n_points ; 
        printf("pi = %lf\n", pi); 
    }
    else{
        for( int i = 0; i < n_threads; i++ ){
            tinfo[i].tid.x = i ;
            if( pthread_create( &tinfo[i].td, &thr_attr, pi_multi, &tinfo[i]) != 0 ){
                printf ("Create pthread error!\n");
                exit (1);
            }
            else{
                printf("Thread-%d created.\n",tinfo[i].td);
            }
        }

        //joining the threads
        
        for(int i = 0; i < n_threads; i++){
            void *res;
            int s = pthread_join(tinfo[i].td, &res);
            if(s != 0){
                handle_error_en(s, "pthread_join");
            }else{
                printf("Thread-%d joined.\n",tinfo[i].td);
            }
        }
        
        double total_points_in = 0;
        for(int i = 0; i < n_threads; i++){
           total_points_in += results[i];
        }
        pi = 4 * total_points_in / n_points; 
        printf("pi = %lf\n", pi); 

    }

    free(results);  
    free(tinfo);
    return 0;
}


