#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <poll.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT "8088"
#define MAXBUF 1024
#define TOTAL 1200
#define MAX_CLIENTS 100

int ssl_send_all(SSL *ssl, const void *buf, int len) {
    int total = 0, n;
    while (total < len) {
        n = SSL_write(ssl, (char*)buf + total, len - total);
        if (n <= 0)
            return -1;
        total += n;
    }
    return total;
}

int ssl_recv_all(SSL *ssl, void *buf, int len) {
    int total = 0, n;
    while (total < len) {
        n = SSL_read(ssl, (char*)buf + total, len - total);
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
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    if (SSL_CTX_use_certificate_file(ctx, "server.crt",SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "server.key",SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    int server_fd, rv;
    struct addrinfo hints, *res, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }
    for (p = res; p != NULL; p = p->ai_next) {
        server_fd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if (server_fd < 0)
            continue;
        int yes = 1;
        setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR, &yes, sizeof(int));
        if (bind(server_fd,p->ai_addr,p->ai_addrlen) == 0)
            break;
        close(server_fd);
    }

    if (!p) {
        printf("Bind failed\n");
        exit(1);
    }
    freeaddrinfo(res);
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(1);
    }
    printf("TLS Server listening on %s\n", PORT);

    struct pollfd fds[MAX_CLIENTS];
    SSL *ssl_clients[MAX_CLIENTS];
    int nfds = 1;
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    int count = 0;
    while (1) {
        int ready = poll(fds, nfds, -1);
        if (ready < 0) {
            perror("poll");
            break;
        }
        for (int i = 0; i < nfds; i++) {
            if (fds[i].fd == server_fd &&
                (fds[i].revents & POLLIN)) {
                int client_fd =accept(server_fd, NULL, NULL);
                if (client_fd < 0)
                    continue;
                SSL *ssl = SSL_new(ctx);
                SSL_set_fd(ssl, client_fd);
                if (SSL_accept(ssl) <= 0) {
                    ERR_print_errors_fp(stderr);
                    close(client_fd);
                    SSL_free(ssl);
                    continue;
                }

                if (nfds < MAX_CLIENTS) {
                    fds[nfds].fd = client_fd;
                    fds[nfds].events = POLLIN;
                    ssl_clients[nfds] = ssl;
                    nfds++;
                    printf("Client connected (fd=%d)\n",
                           client_fd);
                }
                else {
                    close(client_fd);
                    SSL_free(ssl);
                }
            }
            else if (fds[i].revents & POLLIN) {
                int fd = fds[i].fd;
                SSL *ssl = ssl_clients[i];
                uint32_t msg_len;
                if (ssl_recv_all(ssl,&msg_len,sizeof(msg_len)) <= 0) {
                    printf("Client disconnected %d\n", fd);
                    SSL_shutdown(ssl);
                    SSL_free(ssl);
                    close(fd);
                    fds[i] = fds[nfds - 1];
                    ssl_clients[i] = ssl_clients[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }

                msg_len = ntohl(msg_len);
                if (msg_len > MAXBUF) {
                    SSL_shutdown(ssl);
                    SSL_free(ssl);
                    close(fd);
                    fds[i] = fds[nfds - 1];
                    ssl_clients[i] = ssl_clients[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }
                char msg[MAXBUF + 1];
                if (ssl_recv_all(ssl,msg,msg_len) <= 0) {
                    SSL_shutdown(ssl);
                    SSL_free(ssl);
                    close(fd);
                    fds[i] = fds[nfds - 1];
                    ssl_clients[i] = ssl_clients[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }

                msg[msg_len] = '\0';
                count++;
                char timebuf[64];
                get_time(timebuf, sizeof(timebuf));
                printf("\n----- Client -----\n");
                printf("FD    : %d\n", fd);
                printf("Msg   : %s\n", msg);
                printf("Time  : %s\n", timebuf);
                printf("Count : %d\n", count);
                printf("------------------\n");
                char reply[TOTAL];
                snprintf(reply, TOTAL,"Message: %s | Time: %s | Count: %d", msg, timebuf, count);
                uint32_t rlen = strlen(reply);
                uint32_t net  = htonl(rlen);
                ssl_send_all(ssl, &net, sizeof(net));
                ssl_send_all(ssl, reply, rlen);
            }
        }
    }
    close(server_fd);
    SSL_CTX_free(ctx);
    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~/05-02-26$ ./server
TLS Server listening on 8088
Client connected (fd=4)
Client connected (fd=5)
Client connected (fd=6)
Client connected (fd=7)

----- Client -----
FD    : 7
Msg   : hi
Time  : 2026-02-05 13:28:19
Count : 1
------------------

----- Client -----
FD    : 6
Msg   : hello
Time  : 2026-02-05 13:28:25
Count : 2
------------------

----- Client -----
FD    : 5
Msg   : hi
Time  : 2026-02-05 13:28:28
Count : 3
------------------

----- Client -----
FD    : 4
Msg   : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaBCDEFGHIJKLMNOPQRST
Time  : 2026-02-05 13:28:46
Count : 4
------------------

----- Client -----
FD    : 4
Msg   : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaBCDEFGHIJKLMNOPQRST
Time  : 2026-02-05 13:28:53
Count : 5
------------------
Client disconnected 7
Client disconnected 6
Client disconnected 5
Client disconnected 4
*/