#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>

int main(int argc, char* argv[])
{
	__m128 x = _mm_set1_ps(1.0f);
	__m128 y = _mm_set1_ps(1.0f);
	__m128 z ;
	for (int i=0; i < 1000000; i++)
	{
        asm("nop");
        z = _mm_add_ps(x, y);	
        /*
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
		z = _mm_add_ps(x, y);
	*/
        asm("nop");
	}
	return 0;
}
