#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/stat.h>

#define MAX_EVENTS 10000
#define BUFFER_SIZE 8192
#define WWW_ROOT "/home/subiksha/16-02-26/www"
#define UPLOAD_DIR "/home/subiksha/16-02-26/www/uploads"

void set_nonblocking(int fd) {
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}

void send_response(int client, const char *status, const char *type, const char *body) {
    char header[BUFFER_SIZE];
    sprintf(header,
        "HTTP/1.0 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "\r\n",
        status, type, strlen(body));

    send(client, header, strlen(header), 0);
    send(client, body, strlen(body), 0);
}

void handle_get(int client, char *path) {
    char fullpath[512];

    if (strcmp(path, "/") == 0)
        path = "/index.html";

    snprintf(fullpath, sizeof(fullpath), "%s%s", WWW_ROOT, path);

    FILE *fp = fopen(fullpath, "rb");
    if (!fp) {
        send_response(client, "404 Not Found", "text/plain", "File Not Found");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char header[BUFFER_SIZE];
    sprintf(header,
        "HTTP/1.0 200 OK\r\n"
        "Content-Length: %ld\r\n"
        "\r\n",
        size);

    send(client, header, strlen(header), 0);

    char buffer[BUFFER_SIZE];
    size_t n;
    while ((n = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        send(client, buffer, n, 0);
    }

    fclose(fp);
}

void save_uploaded_file(char *body, char *boundary) {
    char *file_start = strstr(body, "filename=\"");
    if (!file_start) return;

    file_start += 10;
    char filename[256];
    sscanf(file_start, "%[^\"]", filename);

    char *data_start = strstr(body, "\r\n\r\n");
    if (!data_start) return;
    data_start += 4;

    char end_boundary[256];
    sprintf(end_boundary, "\r\n--%s", boundary);

    char *data_end = strstr(data_start, end_boundary);
    if (!data_end) return;

    int file_size = data_end - data_start;

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    FILE *fp = fopen(filepath, "wb");
    if (!fp) return;

    fwrite(data_start, 1, file_size, fp);
    fclose(fp);
}

void handle_post(int client, char *request) {
    char *content_type = strstr(request, "Content-Type:");
    char *body = strstr(request, "\r\n\r\n");
    if (!body) {
        send_response(client, "400 Bad Request", "text/plain", "Invalid POST");
        return;
    }

    body += 4;

    if (content_type && strstr(content_type, "multipart/form-data")) {
        char *boundary_pos = strstr(content_type, "boundary=");
        if (!boundary_pos) {
            send_response(client, "400 Bad Request", "text/plain", "No Boundary");
            return;
        }

        char boundary[128];
        sscanf(boundary_pos, "boundary=%s", boundary);

        save_uploaded_file(body, boundary);

        send_response(client, "200 OK", "text/plain", "File Uploaded");
    } else {
        FILE *fp = fopen("post_data.txt", "a");
        if (fp) {
            fprintf(fp, "%s\n", body);
            fclose(fp);
        }
        send_response(client, "200 OK", "text/plain", "POST Data Saved");
    }
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    struct addrinfo hints, *res;
    int server_fd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, argv[1], &hints, &res);

    server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(server_fd, res->ai_addr, res->ai_addrlen);
    listen(server_fd, SOMAXCONN);

    set_nonblocking(server_fd);

    int epoll_fd = epoll_create1(0);

    struct epoll_event event, events[MAX_EVENTS];
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);

    printf("Server running on port %s...\n", argv[1]);

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == server_fd) {

                int client = accept(server_fd, NULL, NULL);
                set_nonblocking(client);

                event.events = EPOLLIN;
                event.data.fd = client;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client, &event);

            } else {

                int client = events[i].data.fd;
                char buffer[BUFFER_SIZE];

                int bytes = recv(client, buffer, BUFFER_SIZE - 1, 0);
                if (bytes <= 0) {
                    close(client);
                    continue;
                }

                buffer[bytes] = '\0';

                char method[10], path[256];
                sscanf(buffer, "%s %s", method, path);

                if (strcmp(method, "GET") == 0) {
                    handle_get(client, path);
                }
                else if (strcmp(method, "POST") == 0) {
                    if (strcmp(path, "/upload") == 0) {
        handle_post(client, buffer);
    }
    else if (strcmp(path, "/submit") == 0) {
        handle_post(client, buffer);
    }
    else {
        send_response(client, "404 Not Found", "text/plain", "Invalid POST URL");
    }
                }
                else {
                    send_response(client, "501 Not Implemented", "text/plain", "Method Not Supported");
                }

                close(client);
            }
        }
    }

    close(server_fd);
    return 0;
}
