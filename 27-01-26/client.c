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
    int sockfd;
    struct sockaddr_in server_addr;
    char *msg = "Hello from client!";

    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
    memset(&(server_addr.sin_zero), '\0', 8);


    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof server_addr) == -1) {
        perror("connect");
        close(sockfd);
        exit(1);
    }

    if (send(sockfd, msg, strlen(msg), 0) == -1) {
        perror("send");
    } else {
        printf("Client: message sent to server.\n");
    }


    close(sockfd);

    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~/27-01-26$ gcc client.c -o client
subiksha@DESKTOP-CBQDRR5:~/27-01-26$ ./client
Client: message sent to server.
*/