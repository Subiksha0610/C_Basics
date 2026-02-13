#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/stat.h>

#define MAX_EVENTS 1000
#define BUFFER_SIZE 8192
#define WWW_ROOT "/var/www"
#define UPLOAD_DIR "/var/www/uploads"

void send_response(int client_fd, int status, const char *status_text,const char *content_type, const char *body, int body_len)
{
    char header[1024];
    sprintf(header,"HTTP/1.0 %d %s\r\n" "Content-Type: %s\r\n" "Content-Length: %d\r\n" "\r\n",status, status_text, content_type, body_len);
    send(client_fd, header, strlen(header), 0);
    if (body_len > 0)
        send(client_fd, body, body_len, 0);
}

void handle_get(int client_fd, char *path)
{
    char fullpath[512];
    if (strcmp(path, "/") == 0)
        path = "/index.html";
    snprintf(fullpath, sizeof(fullpath), "%s%s", WWW_ROOT, path);
    FILE *fp = fopen(fullpath, "rb");
    if (!fp)
    {
        send_response(client_fd, 404, "Not Found","text/plain", "File Not Found", 14);
        return;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);

    char *data = malloc(size);
    fread(data, 1, size, fp);
    fclose(fp);

    send_response(client_fd, 200, "OK","text/html", data, size);
    free(data);
}

void handle_post(int client_fd, char *headers, char *body, int content_length)
{
    if (strstr(headers, "multipart/form-data"))
    {
        char *filename_start = strstr(body, "filename=\"");
        if (!filename_start)
        {
            send_response(client_fd, 400, "Bad Request","text/plain", "No File", 7);
            return;
        }

        filename_start += 10;
        char filename[256];
        sscanf(filename_start, "%[^\"]", filename);

        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

        char *file_data = strstr(body, "\r\n\r\n");
        file_data += 4;

        char *end = strstr(file_data, "\r\n");
        int file_size = end - file_data;

        FILE *fp = fopen(filepath, "wb");
        fwrite(file_data, 1, file_size, fp);
        fclose(fp);

        send_response(client_fd, 200, "OK", "text/plain", "File Uploaded", 13);
    }
    else
    {
        FILE *fp = fopen(WWW_ROOT "/post_data.txt", "a");
        fwrite(body, 1, content_length, fp);
        fclose(fp);
        send_response(client_fd, 200, "OK", "text/plain", "POST Data Saved", 15);
    }
}

void handle_request(int client_fd)
{
    char buffer[BUFFER_SIZE];
    int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes <= 0)
        return;

    buffer[bytes] = '\0';

    char method[10], path[256], version[20];
    sscanf(buffer, "%s %s %s", method, path, version);

    char *headers_end = strstr(buffer, "\r\n\r\n");
    char *body = NULL;
    int content_length = 0;

    if (headers_end)
    {
        body = headers_end + 4;
        char *cl = strstr(buffer, "Content-Length:");
        if (cl)
            sscanf(cl, "Content-Length: %d", &content_length);
    }

    if (strcmp(method, "GET") == 0)
        handle_get(client_fd, path);
    else if (strcmp(method, "POST") == 0)
        handle_post(client_fd, buffer, body, content_length);
    else
        send_response(client_fd, 400, "Bad Request", "text/plain", "Unsupported Method", 18);
}

int create_server_socket(char *port)
{
    struct addrinfo hints, *res, *p;
    int server_fd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, port, &hints, &res);

    for (p = res; p != NULL; p = p->ai_next)
    {
        server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if (server_fd == -1)
            continue;

        int yes = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(server_fd, p->ai_addr, p->ai_addrlen) == 0)
            break;

        close(server_fd);
    }

    freeaddrinfo(res);

    listen(server_fd, SOMAXCONN);
    return server_fd;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    mkdir(UPLOAD_DIR, 0777);

    int server_fd = create_server_socket(argv[1]);

    int epfd = epoll_create1(0);

    struct epoll_event ev, events[MAX_EVENTS];
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;

    epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

    printf("Server running on port %s...\n", argv[1]);

    while (1)
    {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);

        for (int i = 0; i < nfds; i++)
        {
            if (events[i].data.fd == server_fd)
            {
                int client_fd = accept(server_fd, NULL, NULL);

                ev.events = EPOLLIN;
                ev.data.fd = client_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
            }
            else
            {
                int client_fd = events[i].data.fd;

                handle_request(client_fd);

                close(client_fd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, NULL);
            }
        }
    }

    close(server_fd);
    return 0;
}
