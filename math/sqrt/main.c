#include<math.h>
#include<stdio.h>


int main(int argc, char* argv[]){
    int i,j;
    int n_loop;
    double res=0;

    if(argc<2){
        printf("Usage : ./sqrt n_loop\n");
        return -1;
    }

    n_loop = atoi(argv[1]);

    for(i=0;i<n_loop;i++){
        res = sqrt(i*i+0.1+(i*i)%13);
    }

    return 0;
}
