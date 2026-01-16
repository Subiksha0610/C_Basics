#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int fd;
    int read;
    int write;
    int unbuf;
    int eof;
    int err;
} FILEX;

FILEX iob[OPEN_MAX];

FILEX *fopenx(const char *name, const char *mode) {
    int fd;
    FILEX *fp;

    for (fp = iob; fp < iob + OPEN_MAX; fp++) {
        fp->read = fp->write = fp->unbuf = fp->eof = fp->err = 0;
        fp->cnt = 0;
        fp->ptr = fp->base = NULL;
        fp->fd = -1;
    }

    if (*mode == 'r')
        fd = open(name, O_RDONLY, 0);
    else if (*mode == 'w')
        fd = creat(name, 0666);
    else if (*mode == 'a') {
        fd = open(name, O_WRONLY, 0);
        if (fd == -1)
            fd = creat(name, 0666);
        if (fd != -1 && lseek(fd, 0L, SEEK_END) < 0)
            return NULL;
    } else
        return NULL;

    if (fd == -1)
        return NULL;

    for (fp = iob; fp < iob + OPEN_MAX; fp++)
        if (fp->read == 0 && fp->write == 0)
            break;

    if (fp >= iob + OPEN_MAX) {
        close(fd);
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->ptr = NULL;
    fp->unbuf = 0;
    fp->eof = 0;
    fp->err = 0;
    fp->read = (*mode == 'r');
    fp->write = !fp->read;

    return fp;
}

int _fillbuf(FILEX *fp) {
    int bufsize;

    if (fp == NULL || !fp->read || fp->eof || fp->err)
        return EOF;

    bufsize = fp->unbuf ? 1 : BUFSIZE;

    if (fp->base == NULL) {
        fp->base = (char *)malloc(bufsize);
        if (fp->base == NULL) {
            fp->err = 1;
            return EOF;
        }
    }

    fp->cnt = read(fp->fd, fp->base, bufsize);
    if (fp->cnt < 0) {
        fp->err = 1;
        free(fp->base);
        fp->base = NULL;
        return EOF;
    }

    if (fp->cnt == 0) {
        fp->eof = 1;
        return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt--;
    return (unsigned char)*fp->ptr++;
}

int main(void) {
    FILEX *fp;
    int c;

    fp = fopenx("test.txt", "r");
    if (fp == NULL) {
        perror("fopenx failed");
        return 1;
    }

    while ((c = _fillbuf(fp)) != EOF)
        putchar(c);

    return 0;
}
