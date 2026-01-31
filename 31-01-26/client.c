
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#define PORT "8080"
#define BUFFER_SIZE 1024

int main() {
    struct addrinfo hints, *servinfo, *p;
    int sockfd, rv;
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("127.0.0.1", PORT,&hints, &servinfo)) != 0) {
        fprintf(stderr, "error in creating socket\n");
        return 1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if (sockfd < 0) 
        continue;
        if (connect(sockfd,p->ai_addr,p->ai_addrlen) < 0) {
            close(sockfd);
            continue;
        }
        break;
    }
    freeaddrinfo(servinfo);

    if (!p) {
        printf("Connection failed\n");
        return 2;
    }

    printf("Connected to server\n");
    while (1) {
        printf("Enter message: ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0;
        if (!strcmp(message, "exit")) break;
        time_t now = time(NULL);
        char timestr[100];
        strftime(timestr, sizeof timestr,"%Y-%m-%d %H:%M:%S",localtime(&now));
        
        char final_msg[BUFFER_SIZE];
        snprintf(final_msg, BUFFER_SIZE,"%s | Timestamp: %s",message, timestr);
        send(sockfd, final_msg,strlen(final_msg), 0);
        memset(buffer, 0, BUFFER_SIZE);
        recv(sockfd, buffer, BUFFER_SIZE, 0);
        printf("Server: %s\n", buffer);
    }
    close(sockfd);
    return 0;
}
/*output
client 1-
Connected to server
Enter message: hi
Server: Message: hi | Timestamp: 2026-01-31 16:51:48 | Count: 1
Enter message: hi
Server: Message: hi | Timestamp: 2026-01-31 16:51:49 | Count: 2
Enter message: exit

client 2-
Connected to server
Enter message: hello from client 2
Server: Message: hello from client 2 | Timestamp: 2026-01-31 16:52:21 | Count: 3
Enter message: exit

client 3-
Connected to server
Enter message: hello from client 3
Server: Message: hello from client 3 | Timestamp: 2026-01-31 16:52:42 | Count: 4
Enter message: exit
*/