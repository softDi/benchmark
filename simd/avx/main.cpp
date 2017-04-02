#include <immintrin.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
using namespace std;

union U256f {
    __m256 v;
    float a[8];
};

void avx_print(const __m256 v)
{
    const U256f u = { v };

    for (int i = 0; i < 8; ++i)
        printf("%x ",u.a[i]);
    printf("\n");
}

int main() {
    float out[8];
    float a[8] = { 0.0,1.0,2.0,3.0,4.0,5.0,6.0,7};
    __m256 test =  _mm256_load_ps(&a[0]);
    avx_print(test);
    //cout << "  "<< test << endl; // prints 
    return 0;
}
