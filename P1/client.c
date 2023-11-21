 /*
** client02.c -- a datagram
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
#include <netdb.h>

#define MYPORT 4950 // no port server yang digunakan

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in their_addr; // ip server
    struct hostent *he;
    int numbytes;
   
    if (argc != 3)
    {
        fprintf(stderr,"usage: client hostname message\n");
        exit(1);
    }

    // dpt info tentang host
    if ((he=gethostbyname(argv[1])) == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET; // host byte order
    their_addr.sin_port = htons(MYPORT); // host to network short
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8); // set semua nilai ke 0

    if ((numbytes=sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
    {
        perror("sendto");
        exit(1);
    }

    printf("Kirim %d byte ke %s\n", numbytes,
    inet_ntoa(their_addr.sin_addr));
    close(sockfd);
   
    return 0;
}