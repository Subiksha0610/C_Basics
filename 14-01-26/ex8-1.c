/*Exercise 8-1. Rewrite the program cat from Chapter 7
 using read, write, open, and close 
instead of their standard library equivalents. Perform experiments to determine the relative 
speeds of the two versions.  */
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
/*output
subiksha@DESKTOP-CBQDRR5:~$ ./ex8-1 file1.txt
Hello
World
------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ ./ex8-1 file2.txt
Line 1
 Line 2
 Line 3
 Line 4
 Line 5
 Line 6
 Line 7
 Line 8
 9
Line 10
 Line 11
 Line 12
 Line 13
 Line 14
 15
Line 16
 Line 17
 Line 18
 Line 19
 Line 20
Line 21
 Line 22
 Line 23
 Line 24
 Line 25
 Line 26
 Line 27
 Line 28
 Line 29
Line 30
Line 31
Line 32
Line 33
Line 34
Line 35
Line 36
Line 37
Line 38
Line 39
Line 40
Line 41
42
Line 43
Line 44
Line 45
Line 46
Line 47
Line 48
Line 49
Line 50
Line 51
Line 52
------------------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ ./ex8-1 empty.txt
-------------------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ ./ex8-1 empty1.txt
open error: No such file or directory
---------------------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ ./ex8-1 empty.txt file1.txt file2.txt
Hello
World
Line 1
 Line 2
 Line 3
 Line 4
 Line 5
 Line 6
 Line 7
 Line 8
 9
Line 10
 Line 11
 Line 12
 Line 13
 Line 14
 15
Line 16
 Line 17
 Line 18
 Line 19
 Line 20
Line 21
 Line 22
 Line 23
 Line 24
 Line 25
 Line 26
 Line 27
 Line 28
 Line 29
Line 30
Line 31
Line 32
Line 33
Line 34
Line 35
Line 36
Line 37
Line 38
Line 39
Line 40
Line 41
42
Line 43
Line 44
Line 45
Line 46
Line 47
Line 48
Line 49
Line 50
Line 51
Line 52
*/