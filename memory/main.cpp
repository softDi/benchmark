#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	float *data;
	if(argc<2){
		printf("Usage: ./mem counts\n");	
	    return -1;
    }
	int num = atoi(argv[1]);
	data = (float*) malloc(num*sizeof(float));
	for(int i=0; i<num; i++){
		asm("nop");
        
        data[i]=178.0*i;
        
        asm("nop");
    }
	free(data);	
	return 0;
}
