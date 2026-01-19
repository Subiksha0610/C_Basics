/*Exercise 8-3. Design and write _flushbuf, fflush, and fclose. */
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
int fflushx(FILEX *fp);

FILEX iob[OPEN_MAX];

FILEX *fopenx(const char *name, const char *mode) {
    int fd;
    FILEX *fp;

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

    if (fd == -1) return NULL;

    for (fp = iob; fp < iob + OPEN_MAX; fp++)
        if (!fp->read && !fp->write)
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
        fp->base = malloc(bufsize);
        if (fp->base == NULL) {
            fp->err = 1;
            return EOF;
        }
    }

    fp->cnt = read(fp->fd, fp->base, bufsize);
    if (fp->cnt <= 0) {
        if (fp->cnt == 0)
            fp->eof = 1;
        else
            fp->err = 1;
        fp->cnt = 0;
        return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt--;
    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int c, FILEX *fp) {
    int bufsize, n;

    if (fp == NULL || !fp->write || fp->err)
        return EOF;

    bufsize = fp->unbuf ? 1 : BUFSIZE;

    if (fp->base == NULL) {
        fp->base = malloc(bufsize);
        if (fp->base == NULL) {
            fp->err = 1;
            return EOF;
        }
        fp->ptr = fp->base;
        fp->cnt = bufsize;
    }

    if (c == EOF)
        return fflushx(fp);

    if (fp->ptr > fp->base) {
        n = write(fp->fd, fp->base, fp->ptr - fp->base);
        if (n != fp->ptr - fp->base) {
            fp->err = 1;
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = bufsize;

    *fp->ptr++ = (char)c;
    fp->cnt--;
    return c;
}

int fflushx(FILEX *fp) {
    int n;

    if (fp == NULL) {
        for (fp = iob; fp < iob + OPEN_MAX; fp++)
            if (fp->write)
                fflushx(fp);
        return 0;
    }

    if (!fp->write || fp->err || fp->base == NULL)
        return EOF;

    if (fp->ptr == fp->base)
        return 0;

    n = write(fp->fd, fp->base, fp->ptr - fp->base);
    if (n != fp->ptr - fp->base) {
        fp->err = 1;
        return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt = fp->unbuf ? 1 : BUFSIZE;
    return 0;
}

int fclosex(FILEX *fp) {
    if (fp == NULL || (!fp->read && !fp->write))
        return EOF;

    if (fp->write)
        fflushx(fp);

    if (fp->base)
        free(fp->base);

    close(fp->fd);

    fp->fd = -1;
    fp->base = fp->ptr = NULL;
    fp->cnt = 0;
    fp->read = fp->write = 0;
    fp->unbuf = fp->eof = fp->err = 0;

    return 0;
}

int main(void) {
    FILEX *fp;
    int c;

    fp = fopenx("out.txt", "w");
    const char *s = "Hello\n";
    for (const char *p = s; *p; p++)
        _flushbuf(*p, fp);
    _flushbuf(EOF, fp);
    fclosex(fp);

    fp = fopenx("out.txt", "r");
    while ((c = _fillbuf(fp)) != EOF)
        putchar(c);
    fclosex(fp);

    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~$ ./ex8-3
Hello
*/