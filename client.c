/***********************************************************************/
/**      Author: Vaibhav Kapoor                                       **/
/**        Date: Jan. 22 2017                                         **/
/** Description: Client program                                       **/
/***********************************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char **argv)
{
    int sockfd, n, msg_count, portnum;
    char sendline[255];
    char recvline[255];
    struct sockaddr_in servaddr;

    if(argc < 3)
    {
        fprintf(stderr,"usage: %s ip port\n", argv[0]);
        exit(0);
    }

    portnum = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    if(sockfd < 0)
        error("ERROR: opening socket");

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(portnum);

    if(inet_pton(AF_INET, argv[1], &(servaddr.sin_addr)) <= 0)
        error("ERROR: converting ip address");

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        error("ERROR: connecting failed");

    while(1)
    {
        bzero(sendline, 255);
        bzero(recvline, 255);
        sprintf(sendline, "Message count: %d\n", msg_count);

        n = write(sockfd, sendline, strlen(sendline) + 1);
        if(n < 0)
            error("ERROR: writing to socket");

        n = read(sockfd, recvline, 100);
        if(n < 0)
            error("ERROR: reading from socket");

        printf("%s", recvline);
        msg_count++;
        sleep(1);
    }
}
