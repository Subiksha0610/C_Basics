#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define BUF 4096

void send_file_upload(int sock)
{
    FILE *fp = fopen("test.txt", "rb");
    if (!fp) {
        printf("test.txt not found!\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    char *filedata = malloc(filesize);
    fread(filedata, 1, filesize, fp);
    fclose(fp);

    char boundary[] = "----WebKitFormBoundary12345";

    char body[65536];

    int body_len = sprintf(body,
        "--%s\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"test.txt\"\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n",
        boundary);

    memcpy(body + body_len, filedata, filesize);
    body_len += filesize;

    body_len += sprintf(body + body_len,
        "\r\n--%s--\r\n",
        boundary);

    char header[1024];

    int header_len = sprintf(header,
        "POST /upload HTTP/1.1\r\n"
        "Host: 127.0.0.1:8080\r\n"
        "Content-Type: multipart/form-data; boundary=%s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n",
        boundary, body_len);

    send(sock, header, header_len, 0);

    send(sock, body, body_len, 0);

    free(filedata);

    printf("File upload request sent\n");
}


int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s ip port\n", argv[0]);
        return 0;
    }

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    getaddrinfo(argv[1], argv[2], &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);

    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        perror("connect");
        return 1;
    }

    send_file_upload(sock);

    char buf[BUF];
    int n;

    printf("\nServer Response\n");

    while ((n = recv(sock, buf, sizeof(buf)-1, 0)) > 0) {
        buf[n] = 0;
        printf("%s", buf);
    }

    close(sock);
    return 0;
}


/*output
1.GET request inside client
subiksha@DESKTOP-CBQDRR5:~/http_project$ ./client 127.0.0.1 8080 /
HTTP/1.1 200 OK
Content-Type:text/html

<html>
<body>
<h1>My C HTTP Server</h1>
<a href="upload.html">Upload</a>
</body>
</html>


2. GET request using curl
subiksha@DESKTOP-CBQDRR5:~/http_project$ curl http://127.0.0.1:8080/
<html>
<body>
<h1>My C HTTP Server</h1>
<a href="upload.html">Upload</a>
</body>
</html>

3. GET req using curl for accessing the test.txt file content
subiksha@DESKTOP-CBQDRR5:~/http_project$ curl http://127.0.0.1:8080/test.txt
hello world

4. GET req using browser
shows form 

5.POST req using curl only for data
curl -X POST -d "abc" http://127.0.0.1:8080/
Data Received

curl -X POST -d "name=Subiksha&id=101" http://127.0.0.1:8080/1:8080/
Data Received

6.POST req using curl for uploading file
curl -F "file=@test.txt" http://127.0.0.1:8080/
File Uploaded

7. POST req using curl for uploading file and data
curl -F "username=Subiksha" -F "file=@test.txt" http://127.0.0.1:8080/
File Uploaded

8. PUT request using curl ( changing the content of test.txt file )
curl -X PUT -d "new" http://127.0.0.1:8080/test.txt

9. DELETE request using curl ( test.txt file deleted )
curl -X DELETE http://127.0.0.1:8080/test.txtest.txt
Deleted

*/