#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>


void *shm_alloc(int n, int size,int *shm_id,key_t key){
     int shm_size = n*size;
     char *arr;
     *shm_id = shmget(key,shm_size,00666|IPC_CREAT);
     arr = (char *)shmat(*shm_id,NULL,0);
     if(!arr){
        perror("shmat");
        return NULL;
     }
     return (void*)arr;
}


int main(int argc,char *argv[]){

    unsigned char *buf;
    int shm_id=0,i;
    buf =  shm_alloc(50,sizeof(unsigned char),&shm_id,1111);
    for(i=0;i<50;i++)
       buf[i]=1;
    return 0;
}
