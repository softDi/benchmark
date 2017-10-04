#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <omp.h>

int main(int argc, char* argv[])
{

    if (argc < 2) {
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);

    omp_set_num_threads(4);

    double* a = (double*)malloc(width * width * sizeof(double));
    double* b = (double*)malloc(width * width * sizeof(double));
    double* c = (double*)malloc(width * width * sizeof(double));

    //double *A = (double*)__builtin_assume_aligned(a, 16);
    //double *B = (double*)__builtin_assume_aligned(b, 16);
    //double *C = (double*)__builtin_assume_aligned(c, 16);
    double* A = a;
    double* B = b;
    double* C = c;

    #pragma omp parallel for schedule(static) shared(A, B, C)
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < width; k++) {
                asm("nop");
                C[i * width + j] += A[i * width + k] * B[k * width + j];
                asm("nop");
            }
        }
    }

    //    for(int i=0; i<width; i++){
    //        for(int j=0; j<width; j++){
    //            printf("%lf ",C[ i*width + j ]);
    //        }
    //        printf("\n");
    //    }

    if (A) {
        free(A);
    };
    if (B) {
        free(B);
    };
    if (C) {
        free(C);
    };

    return 0;
}
