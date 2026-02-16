#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 8192

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        printf("Usage: %s <host> <port> <GET/POST> <path>\n", argv[0]);
        return 1;
    }

    char *host = argv[1];
    char *port = argv[2];
    char *method = argv[3];
    char *path = argv[4];

    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(host, port, &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(sockfd, res->ai_addr, res->ai_addrlen);

    char request[BUFFER_SIZE];

    if (strcmp(method, "GET") == 0)
    {
        sprintf(request,
                "GET %s HTTP/1.0\r\n"
                "Host: %s\r\n"
                "\r\n",
                path, host);
    }
    else
    {
        char body[] = "name=testclient";
        sprintf(request,
                "POST %s HTTP/1.0\r\n"
                "Host: %s\r\n"
                "Content-Type: application/x-www-form-urlencoded\r\n"
                "Content-Length: %ld\r\n"
                "\r\n"
                "%s",
                path, host, strlen(body), body);
    }

    send(sockfd, request, strlen(request), 0);

    char buffer[BUFFER_SIZE];
    int bytes;

    while ((bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }

    close(sockfd);
    freeaddrinfo(res);
    return 0;
}
