
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVERPORT 4950  

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in broadcast_addr;
    int broadcast = 1;
    int numbytes;

    if (argc != 2) {
        fprintf(stderr, "usage: %s message\n", argv[0]);
        exit(1);
    }

  
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                   sizeof broadcast) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

  
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(SERVERPORT);
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    memset(broadcast_addr.sin_zero, '\0', sizeof broadcast_addr.sin_zero);

    if ((numbytes = sendto(sockfd, argv[1], strlen(argv[1]), 0,
         (struct sockaddr *)&broadcast_addr, sizeof broadcast_addr)) == -1) {
        perror("sendto");
        exit(1);
    }

    printf("sent %d bytes as broadcast\n", numbytes);

    close(sockfd);
    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~/29-01-26$ ./broadcast hi
sent 2 bytes as broadcast
*/