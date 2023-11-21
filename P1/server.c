 /*
** server02.c -- a datagram sockets "server"
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4950 // no port server
#define MAXBUFLEN 100

int main(void)
{
    int sockfd;
    struct sockaddr_in my_addr; // ip address server
    struct sockaddr_in their_addr; // ip address client
    int addr_len, numbytes;
    char buf[MAXBUFLEN];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET; // host byte order
    my_addr.sin_port = htons(MYPORT); // host to network short
    my_addr.sin_addr.s_addr = INADDR_ANY; // ip address server
    memset(&(my_addr.sin_zero), '\0', 8); // set semua nilai menjadi 0

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    addr_len = sizeof(struct sockaddr);

    if ((numbytes=recvfrom(sockfd,buf, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
    {
        perror("recvfrom");
        exit(1);
    }

    printf("Mendapat paket dari : %s\n",inet_ntoa(their_addr.sin_addr));
    printf("Panjang paket : %d bytes \n",numbytes);
    buf[numbytes] = '\0';
    printf("Isi paket : \"%s\"\n",buf);
    close(sockfd);

    return 0;
}