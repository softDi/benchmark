/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<time.h>
#include<math.h>


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char *buffer;
    unsigned int size_buffer=1;
    
    struct sockaddr_in serv_addr, cli_addr;
    double result=0;
    int i,j,k;
    clock_t t1; 
    char bOnce=0; 
    unsigned int N=1,M=1;
    int n;
    if (argc < 4) {
        fprintf(stderr,"Usage : ./server port MatrixWidth TxRxBufferSize(bytes)\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    
    uint32_t width = atoi(argv[2]);
    size_buffer = atoi(argv[3]);
    if(size_buffer<255){
        printf("buffer size should be equal or larger than 255\n");    
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    do{ 
        double *A = (double*) malloc(width*width*sizeof(double));
        double *B = (double*) malloc(width*width*sizeof(double));
        double *C = (double*) malloc(width*width*sizeof(double));

        newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");

        buffer = (char*) malloc(size_buffer);

        //bzero(buffer,256);
        do{
            n = read(newsockfd,buffer,size_buffer);
            if(buffer[0]=='E'){
                bOnce=1; 
            }
            //printf("expect %u, read %d \n", size_buffer, n );
            t1 = clock();
            if (n < 0) error("ERROR reading from socket");
            for(int i=0; i<width; i++){
                for(int j=0; j<width; j++){
                    for(int k=0; k<width; k++){
                        asm("nop"); 
                        C[ i*width + j ] += A[ i*width + k ] * B[ k*width + j ] ;
                        asm("nop");
                    }
                }
            }
            //printf("dt = %f\n",(clock()-t1)/(float)CLOCKS_PER_SEC);
            //printf("Here is the message: %s\n",buffer);
            sprintf(buffer,"I got your message\n");
            n = write(newsockfd,buffer,size_buffer);
            if (n < 0){
                error("ERROR writing to socket");
            }
        }while(!bOnce);
        close(newsockfd);
        if(A){ free(A); };
        if(B){ free(B); };
        if(C){ free(C); };
    }while(0);
    close(sockfd);
    free(buffer);
    return 0; 
}
