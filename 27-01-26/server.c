#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>    
#include <arpa/inet.h>     

#define PORT 3490   

int main(void) {
    int sockfd, new_fd;
    struct sockaddr_in my_addr, their_addr;
    socklen_t sin_size;
    char ipstr[INET6_ADDRSTRLEN];

    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        perror("listen");
        close(sockfd);
        exit(1);
    }

    printf("Server: waiting for connections...\n");

    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
        perror("accept");
        close(sockfd);
        exit(1);
    }

    struct sockaddr_storage peer_addr;
    socklen_t addr_len = sizeof peer_addr;

    if (getpeername(new_fd, (struct sockaddr*)&peer_addr, &addr_len) == -1) {
        perror("getpeername");
    } else {
        void *addr;
        if (peer_addr.ss_family == AF_INET) {
            struct sockaddr_in *s = (struct sockaddr_in*)&peer_addr;
            addr = &(s->sin_addr);
        } else {
            struct sockaddr_in6 *s = (struct sockaddr_in6*)&peer_addr;
            addr = &(s->sin6_addr);
        }

        inet_ntop(peer_addr.ss_family, addr, ipstr, sizeof ipstr);
        printf("Peer IP: %s\n", ipstr);
    }

    close(new_fd);
    close(sockfd);

    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~/27-01-26$ gcc server.c -o server
subiksha@DESKTOP-CBQDRR5:~/27-01-26$ ./server
Server: waiting for connections...
Peer IP: 127.0.0.1
*/