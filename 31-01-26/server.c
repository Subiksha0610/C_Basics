#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define PORT "8080"
#define BUFFER_SIZE 1024

int message_count = 0;
pthread_mutex_t lock;

void *handle_client(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);
    char buffer[BUFFER_SIZE];
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes = recv(client_fd, buffer,BUFFER_SIZE, 0);
        if (bytes <= 0) {
            printf("Client disconnected: fd %d\n", client_fd);
            break;
        }
        buffer[bytes] = '\0';

        pthread_mutex_lock(&lock);
        message_count++;
        int count = message_count;
        pthread_mutex_unlock(&lock);
        printf("Client %d: %s\n", client_fd, buffer);
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "Message: %s | Count: %d", buffer, count);
        send(client_fd, response, strlen(response), 0);
    }
    close(client_fd);
    return NULL;
}

int main() {
    struct addrinfo hints, *servinfo, *p;
    int listener;
    int rv;
    pthread_mutex_init(&lock, NULL);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT,&hints, &servinfo)) != 0) {
            fprintf(stderr, "error in creating socket\n");
        return 1;
    }
    for (p = servinfo; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family,p->ai_socktype, p->ai_protocol);
        if (listener < 0) 
        continue;
        int yes = 1;
        setsockopt(listener, SOL_SOCKET,SO_REUSEADDR, &yes, sizeof yes);
        if (bind(listener, p->ai_addr,p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }
        break;
    }
    freeaddrinfo(servinfo);
    if (!p) {
        fprintf(stderr, "Bind failed\n");
        return 2;
    }
    if (listen(listener, 10) < 0) {
        perror("listen");
        return 1;
    }
    printf("Server running on port %s\n", PORT);

    while (1) {
        struct sockaddr_storage client_addr;
        socklen_t addr_len = sizeof client_addr;
        int client_fd = accept(listener,(struct sockaddr *)&client_addr,&addr_len);

        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        printf("New client connected: fd %d\n", client_fd);

        int *new_sock = malloc(sizeof(int));
        *new_sock = client_fd;
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, new_sock) != 0) {
            perror("pthread_create");
            close(client_fd);
            free(new_sock);
        }
        pthread_detach(tid);
    }

    close(listener);
    pthread_mutex_destroy(&lock);
    return 0;
}

/*output
Server running on port 8080
New client connected: fd 4
Client 4: hi | Timestamp: 2026-01-31 16:51:48
Client 4: hi | Timestamp: 2026-01-31 16:51:49
New client connected: fd 5
Client 5: hello from client 2 | Timestamp: 2026-01-31 16:52:21
New client connected: fd 6
Client 6: hello from client 3 | Timestamp: 2026-01-31 16:52:42
Client disconnected: fd 6
Client disconnected: fd 5
Client disconnected: fd 4
*/