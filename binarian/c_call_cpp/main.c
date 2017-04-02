#include<stdio.h>

extern  int add( int x,  int y );
int main( int  argc, char*  argv[] )
{
    if( argc <2 ){
        printf("Usage: ./a.out num1 num2\n");
        return -1;
    }
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    printf("%d + %d = %d\n", num1, num2, add(num1, num2)); 
    return 0;
} 

