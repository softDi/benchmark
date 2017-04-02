#include<math.h>
#include<stdio.h>


int main(int argc, char* argv[]){
    int i,j;
    int n_loop;
    double res=0;

    if(argc<2){
        printf("usage : ./compute n_loop\n");
    }

    n_loop = atoi(argv[1]);

    for(i=0;i<n_loop;i++){
        res = (double)i*(double)i+0.1;
        //res = sqrt(i*i+0.1);
    }

    return 0;
}
