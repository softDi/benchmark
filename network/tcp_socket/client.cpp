#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<time.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    clock_t t1;    
    char *buffer;
    unsigned int size_buffer=1;
    unsigned int n_sends=1;
    double result=0;
    int i,j,k,ns;


    if (argc < 5) {
        fprintf(stderr,"Usage: ./client hostname port TxRxBufferSize(bytes) n_sends\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    size_buffer = atoi(argv[3]);
    n_sends = atoi(argv[4]);
    if(size_buffer<255){
        printf("buffer size %u; it should be equal or larger than 255\n",size_buffer);    
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
            (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    //printf("Please enter the message: ");

    buffer = (char*) malloc(size_buffer);
    bzero(buffer,size_buffer);
    for(ns=0; ns<n_sends; ns++){
        sprintf(buffer,"I am a client\n");

        if(ns==n_sends-1){
            buffer[0]='E';
        }
        //fgets(buffer,255,stdin);
        n = write(sockfd,buffer,size_buffer);
        //printf("expect %u, write %u\n",size_buffer, n);
        if (n < 0) 
            error("ERROR writing to socket");
        bzero(buffer,size_buffer);

        n = read(sockfd,buffer,size_buffer);
        if (n < 0) 
            error("ERROR reading from socket");
        //printf("%s\n",buffer);
    }
    close(sockfd); 
    free(buffer);
    return 0;
}
