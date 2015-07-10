/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(/*int argc, char *argv[]*/)
{
     int sockfd, newsockfd, portno;
     int portnumber = 6666;
     socklen_t clilen;
     char buffer[65536+1];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (portnumber/*argc*/ < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_DGRAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = portnumber; //atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     for (;;) {
	     clilen = sizeof(cli_addr);
	     n = recvfrom(sockfd, buffer, sizeof buffer - 1, 0, (struct sockaddr *) &cli_addr, &clilen);
	     if (n < 0) error("ERROR reading from socket");
	     buffer[n] = '\0';
	     printf("%s\n",buffer);
    	     //sleep(500);
	     //system("clear");
    }
    close(sockfd);
    return 0; 
}