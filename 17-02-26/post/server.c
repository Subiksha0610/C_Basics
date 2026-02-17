

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>

#define PORT "8080"
#define BACKLOG 10

#define BUF_SIZE 300000

int  read_request(int sock, char *buffer, int size);
void send_html(int client);
void handle_upload(int client, char *request);
void handle_get_file(int client, char *req);
void handle_put_file(int client, char *req);
void handle_delete_file(int client, char *req);



int read_request(int sock, char *buffer, int size)
{
    int total = 0;
    int n;

    while (1)
    {
        n = recv(sock,buffer + total,size - total - 1,0);

        if (n <= 0)
            break;

        total += n;
        buffer[total] = '\0';

        
        if (strstr(buffer, "\r\n\r\n"))
        {
            char *cl = strstr(buffer, "Content-Length:");

            if (cl)
            {
                int len = atoi(cl + 15);

                char *body = strstr(buffer, "\r\n\r\n");

                int body_len =total - (body - buffer) - 4;

                if (body_len >= len)
                    break;
            }
            else
            {
                break;
            }
        }
    }

    return total;
}


int main()
{
    struct addrinfo hints, *res, *p;
    int server_fd, client_fd;
    int yes = 1;

    char buffer[BUF_SIZE];

    mkdir("uploads", 0777);

    memset(&hints, 0, sizeof hints);

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if (getaddrinfo(NULL, PORT, &hints, &res) != 0)
    {
        perror("getaddrinfo");
        exit(1);
    }

    for (p = res; p; p = p->ai_next)
    {
        server_fd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);

        if (server_fd < 0)
            continue;

        setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes);

        if (bind(server_fd,p->ai_addr,p->ai_addrlen) == 0)
            break;

        close(server_fd);
    }

    if (!p)
    {
        printf("Bind failed\n");
        exit(1);
    }

    freeaddrinfo(res);

    listen(server_fd, BACKLOG);

    printf("Server running at http://localhost:8080\n");

    while (1)
    {
        client_fd = accept(server_fd, NULL, NULL);

        if (client_fd < 0)
            continue;

        memset(buffer, 0, BUF_SIZE);

        int bytes = read_request(client_fd,buffer,BUF_SIZE);

        if (bytes <= 0)
        {
            close(client_fd);
            continue;
        }

        printf("\nRequest Received\n");

if (strncmp(buffer, "GET / ", 6) == 0)
{
    send_html(client_fd);
}

else if (strncmp(buffer, "GET /", 5) == 0)
{
    handle_get_file(client_fd, buffer);
}



else if (strncmp(buffer, "POST /upload", 12) == 0)
{
    handle_upload(client_fd, buffer);
}



else if (strncmp(buffer, "PUT /", 5) == 0)
{
    handle_put_file(client_fd, buffer);
}



else if (strncmp(buffer, "DELETE /", 8) == 0)
{
    handle_delete_file(client_fd, buffer);
}


        close(client_fd);
    }

    close(server_fd);
    return 0;
}


void send_html(int client)
{
    FILE *fp = fopen("index.html", "r");

    if (!fp)
        return;

    char buf[4096];

    char header[] ="HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n";

    send(client, header, strlen(header), 0);

    while (fgets(buf, sizeof(buf), fp))
    {
        send(client, buf, strlen(buf), 0);
    }

    fclose(fp);
}

void handle_upload(int client, char *req)
{
    char *body = strstr(req, "\r\n\r\n");

    if (!body)
        return;

    body += 4;


    char *bptr = strstr(req, "boundary=");

    if (!bptr)
        return;

    char boundary[200];

    sscanf(bptr, "boundary=%199s", boundary);

    char end_boundary[250];

    sprintf(end_boundary, "--%s", boundary);

    char *name_ptr = strstr(body,"name=\"username\"");

    if (!name_ptr)
        return;

    name_ptr = strstr(name_ptr, "\r\n\r\n");

    if (!name_ptr)
        return;

    name_ptr += 4;

    char username[100];

    sscanf(name_ptr, "%99[^\r\n]", username);

    printf("Name: %s\n", username);


    char *file_ptr = strstr(body,"name=\"myfile\"");

    if (!file_ptr)
        return;


    char *fptr = strstr(file_ptr,"filename=\"");

    if (!fptr)
        return;


    char filename[100];

    sscanf(fptr, "filename=\"%99[^\"]\"", filename);

    printf("File: %s\n", filename);


    file_ptr = strstr(file_ptr, "\r\n\r\n");

    if (!file_ptr)
        return;

    file_ptr += 4;


    char filepath[200];

    sprintf(filepath,"uploads/%s", filename);

    FILE *fp = fopen(filepath, "wb");

    if (!fp)
    {
        perror("file open failed");
        return;
    }


    char *end = strstr(file_ptr, end_boundary);

    if (!end)
    {
        fclose(fp);
        return;
    }

    int size = end - file_ptr;

    if (size <= 0)
    {
        fclose(fp);
        return;
    }

    fwrite(file_ptr, 1, size, fp);

    fclose(fp);


    FILE *data = fopen("data.txt", "a");

    if (!data)
    {
        perror("data.txt open failed");
    }
    else
    {
        fprintf(data,"User: %s | File: %s\n",username,filename);

        fflush(data);
        fclose(data);
    }


    char page[] =
        "<html><body>"
        "<h2>Upload Successful</h2>"
        "<a href='/'>Go Back</a>"
        "</body></html>";


    char header[512];

    sprintf(header,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %ld\r\n"
            "Connection: close\r\n\r\n",
            strlen(page));


    send(client, header, strlen(header), 0);
    send(client, page, strlen(page), 0);
}
void handle_get_file(int client, char *req)
{
    char filename[200];

  sscanf(req, "GET /%199[^ ]", filename);


    if (strcmp(filename, "") == 0 ||
        strcmp(filename, " ") == 0)
        return;

    char path[300];

    sprintf(path, "uploads/%s", filename);


    FILE *fp = fopen(path, "rb");

    if (!fp)
    {
        char msg[] =
            "HTTP/1.1 404 Not Found\r\n\r\nFile Not Found";

        send(client, msg, strlen(msg), 0);
        return;
    }


    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);


    char *data = malloc(size);

    fread(data, 1, size, fp);

    fclose(fp);


    char header[512];

    sprintf(header,
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: %ld\r\n"
            "Content-Type: application/octet-stream\r\n"
            "Connection: close\r\n\r\n",
            size);


    send(client, header, strlen(header), 0);
    send(client, data, size, 0);

    free(data);
}
void handle_put_file(int client, char *req)
{
    char filename[200];

 sscanf(req, "PUT /%199[^ ]", filename);

    char *body = strstr(req, "\r\n\r\n");

    if (!body)
        return;

    body += 4;

    char path[300];

    sprintf(path, "uploads/%s", filename);

    FILE *fp = fopen(path, "wb");

    if (!fp)
    {
        perror("PUT open failed");
        return;
    }


    fwrite(body, 1, strlen(body), fp);

    fclose(fp);


    char msg[] ="HTTP/1.1 200 OK\r\n\r\nFile Updated";

    send(client, msg, strlen(msg), 0);
}
void handle_delete_file(int client, char *req)
{
    char filename[200];

sscanf(req, "DELETE /%199[^ ]", filename);

    char path[300];

    sprintf(path, "uploads/%s", filename);

    if (remove(path) == 0)
    {
        char msg[] ="HTTP/1.1 200 OK\r\n\r\nFile Deleted";

        send(client, msg, strlen(msg), 0);
    }
    else
    {
        char msg[] ="HTTP/1.1 404 Not Found\r\n\r\nFile Not Found";

        send(client, msg, strlen(msg), 0);
    }
}
/*output
GET
1. http://localhost:8080/
  shows form 

2. http://localhost:8080/test.txt
  download the file

3. curl http://localhost:8080/test.txt
   curl http://127.0.0.1:8080/data.txt
   curl http://10.249.191.252:8080/data.txt
shows the content of the file

PUT
1. curl -X PUT http://localhost:8080/test.txt -d "New file content"
overwrite the content

DELETE
1. curl -X DELETE http://localhost:8080/test.txt
delete the file

POST
1. http://localhost:8080/
opens form , user upload file and data (data file contains name & files are stored in uploads folder)

2. curl -X POST http://localhost:8080/upload \
  -F "username=vidhya" \
  -F "myfile=@/home/subiksha/post/uploads/data.txt"
post using curl

3. curl -X POST http://localhost:8080/upload   -F "username=heera"   -F "myfile=@/home/subiksha/test.txt"
<html><body><h2>Upload Successful</h2><a href='/'>Go Back</a></body></html>

*/

/*server response
./server
Server running at http://localhost:8080

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received
Name: harini
File: Screenshot (181).png

Request Received
Name: harini
File: Screenshot (181).png

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received

Request Received
Name: vidhya
File: data.txt

Request Received
Name: subiksha
File: DESIGN UNIT 3.pdf

Request Received
Name: heera
File: test.txt
*/