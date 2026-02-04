#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <poll.h>

#define PORT "8088"
#define MAXBUF 1024
#define TOTAL 1200
#define MAX_CLIENTS 100

int send_all(int sock, const void *buf, int len) {
    int total = 0, n;
    while (total < len) {
        n = send(sock, (char *)buf + total, len - total, 0);
        if (n <= 0)
            return -1;
        total += n;
    }
    return total;
}

int recv_all(int sock, void *buf, int len) {
    int total = 0, n;
    while (total < len) {
        n = recv(sock, (char *)buf + total, len - total, 0);
        if (n <= 0)
            return -1;
        total += n;
    }
    return total;
}


void get_time(char *buf, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buf, size, "%Y-%m-%d %H:%M:%S", t);
}

int main() {
    int server_fd, rv;
    struct addrinfo hints, *res, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }
    for (p = res; p != NULL; p = p->ai_next) {
        server_fd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if (server_fd < 0)
            continue;
        int yes = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,&yes, sizeof(int));
        if (bind(server_fd, p->ai_addr, p->ai_addrlen) == 0)
            break;
        close(server_fd);
    }

    if (p == NULL) {
        printf("Bind failed\n");
        exit(1);
    }
    freeaddrinfo(res);
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(1);
    }
    printf("Server listening on port %s\n", PORT);

    struct pollfd fds[MAX_CLIENTS];
    int nfds = 1;
    fds[0].fd     = server_fd;
    fds[0].events = POLLIN;
    int count = 0;

    while (1) {
        int poll_count = poll(fds, nfds, -1);
        if (poll_count < 0) {
            perror("poll");
            break;
        }
        for (int i = 0; i < nfds; i++) {
            if (fds[i].fd == server_fd &&
                (fds[i].revents & POLLIN)) {
                int client_fd = accept(server_fd, NULL, NULL);
                if (client_fd < 0)
                    continue;
                if (nfds < MAX_CLIENTS) {
                    fds[nfds].fd     = client_fd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                    printf("New client connected (fd %d)\n",
                           client_fd);
                }
                else {
                    close(client_fd);
                }
            }
            else if (fds[i].revents & POLLIN) {
                int client_fd = fds[i].fd;
                uint32_t msg_len;
                if (recv_all(client_fd,&msg_len, sizeof(msg_len)) <= 0) {
                    printf("Client disconnected fd %d \n",client_fd);
                    close(client_fd);
                    fds[i] = fds[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }
                msg_len = ntohl(msg_len);
                if (msg_len > MAXBUF) {
                    close(client_fd);
                    fds[i] = fds[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }
                char msg[MAXBUF + 1];
                if (recv_all(client_fd, msg, msg_len) <= 0) {
                    close(client_fd);
                    fds[i] = fds[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }
                msg[msg_len] = '\0';
                count++;
                char server_time[64];
                get_time(server_time, sizeof(server_time));
                printf("\n----- Received From Client -----\n");
                printf("FD           : %d\n", client_fd);
                printf("Message      : %s\n", msg);
                printf("Server Time  : %s\n", server_time);
                //printf("Count        : %d\n", count);
                printf("--------------------------------\n");
                char reply[TOTAL];
                snprintf(reply, TOTAL, "Message: %s | Time: %s | Count: %d", msg, server_time, count);
                uint32_t reply_len = strlen(reply);
                uint32_t net_len   = htonl(reply_len);
                send_all(client_fd, &net_len, sizeof(net_len));
                send_all(client_fd, reply, reply_len);
            }
        }
    }
    close(server_fd);
    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~/03-02-26$ ./server2
Poll Server listening on port 8088...
New client connected (fd=4)

----- Received From Client -----
FD           : 4
Message      : hi
Server Time  : 2026-02-04 04:46:17
Count        : 1
--------------------------------
New client connected (fd=5)

----- Received From Client -----
FD           : 5
Message      : hi
Server Time  : 2026-02-04 04:47:15
Count        : 2
--------------------------------

----- Received From Client -----
FD           : 5
Message      : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaBCDEFGHIJKLMNOPQRST
Server Time  : 2026-02-04 04:47:31
Count        : 3
--------------------------------

----- Received From Client -----
FD           : 4
Message      : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaBCDEFGHIJKLMNOPQRST
Server Time  : 2026-02-04 04:47:38
Count        : 4
--------------------------------
New client connected (fd=6)

----- Received From Client -----
FD           : 6
Message      : hellooo
Server Time  : 2026-02-04 04:48:29
Count        : 5
--------------------------------
Client disconnected (fd=4)
Client disconnected (fd=5)
Client disconnected (fd=6)
*/