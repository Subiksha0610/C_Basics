
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVERPORT 4950   

int main(void) {
    int sockfd;
    struct sockaddr_in my_addr, their_addr;
    socklen_t addr_len;
    char buf[1024];
    int numbytes;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SERVERPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY; 
    memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
        perror("bind");
        exit(1);
    }

    printf("listener: waiting for broadcast messages...\n");

    addr_len = sizeof their_addr;
    while (1) {
        if ((numbytes = recvfrom(sockfd, buf, sizeof buf - 1, 0,
             (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }

        buf[numbytes] = '\0';
        printf("listener: got packet from %s\n", inet_ntoa(their_addr.sin_addr));
        printf("listener: packet contains \"%s\"\n", buf);
    }

    close(sockfd);
    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~/29-01-26$ ./listener
listener: waiting for broadcast messages...
listener: got packet from 172.19.91.124
listener: packet contains "hi"
*/