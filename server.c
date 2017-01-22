/***********************************************************************/
/**      Author: Vaibhav Kapoor                                       **/
/**        Date: Jan. 22 2017                                         **/
/** Description: Server program                                       **/
/***********************************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void processing(int sockfd);

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int listen_fd, comm_fd, pid;

    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0)
        error("ERROR: opening socket");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(8080);

    if(bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        error("ERROR: binding socket");

    listen(listen_fd, 10);

    while(1)
    {
        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
        if(comm_fd < 0)
            error("ERROR: accepting client connection");
        pid = fork();
        if(pid < 0)
            error("ERROR: forking");
        if(pid == 0)
        {
            printf("launching connection\n");
            close(listen_fd);
            processing(comm_fd);
            exit(0);
        }
        else
            close(comm_fd);
    }
}

void processing(int sockfd)
{
    while(1) {
        int n;
        char str[255];

        bzero(str, 255);

        n = read(sockfd, str, 255);
        if(n < 0)
            error("ERROR: reading from socket");
        /*printf("Echoing back - %s", str);*/
        n = write(sockfd, str, strlen(str)+1);
        if(n < 0)
            error("ERROR: writing to socket");
    }
}

