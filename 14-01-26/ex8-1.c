#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int fd;
    ssize_t n;
    char buf[BUFSIZE];
    int status = 0;

    if (argc == 1) {
        while ((n = read(STDIN_FILENO, buf, BUFSIZE)) != 0) {
            if (n < 0) {
                perror("read error");
                return 1;
            }
            if (write(STDOUT_FILENO, buf, n) != n) {
                perror("write error");
                return 1;
            }
        }
    } else {
        while (--argc > 0) {
            fd = open(*++argv, O_RDONLY);
            if (fd < 0) {
                perror("open error");
                status = 1;
                continue;
            }
            while ((n = read(fd, buf, BUFSIZE)) != 0) {
                if (n < 0) {
                    perror("read error");
                    status = 1;
                    break;
                }
                if (write(STDOUT_FILENO, buf, n) != n) {
                    perror("write error");
                    close(fd);
                    return 1;
                }
            }
            if (close(fd) < 0) {
                perror("close error");
                status = 1;
            }
        }
    }
    return status;
}
