#include<cmath>
#include<cstdlib>
#include<stdio.h>
#include<stdint.h>
int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);

    double *A = (double*) malloc(width*width*sizeof(double));
    double *B = (double*) malloc(width*width*sizeof(double));
    double *C = (double*) malloc(width*width*sizeof(double));
    
    for(int i=0; i<width; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<width; k++){
                asm("nop"); 
		C[ i*width + j ] += A[ i*width + k ] * B[ k*width + j ] ;
            	asm("nop");
	    }
        }
    }

    if(A){ free(A); };
    if(B){ free(B); };
    if(C){ free(C); };

    return 0;
}
