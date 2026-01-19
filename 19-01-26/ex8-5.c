#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define MAXPATH 1024

void fsize(char *name);
void dirwalk(char *dir, void (*fcn)(char *));

int main(int argc, char **argv) {
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
    return 0;
}

void dirwalk(char *dir, void (*fcn)(char *)) {
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        if (strlen(dir) + strlen(dp->d_name) + 2 > MAXPATH) {
            fprintf(stderr, "path too long: %s/%s\n", dir, dp->d_name);
            continue;
        }

        char name[MAXPATH];
        snprintf(name, sizeof(name), "%s/%s", dir, dp->d_name);
        (*fcn)(name);
    }
    closedir(dfd);
}

void fsize(char *name) {
    struct stat st;

    if (lstat(name, &st) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    printf("%8ld bytes  ", (long) st.st_size);
    printf("links: %ld  ", (long) st.st_nlink);
    printf("uid: %d  gid: %d  ", st.st_uid, st.st_gid);
    printf("mode: %o  ", st.st_mode & 07777);
    printf("modified: %s", ctime(&st.st_mtime));
    printf("name: %s\n", name);

    if (S_ISLNK(st.st_mode))
        return;

    if (S_ISDIR(st.st_mode)) {
        dirwalk(name, fsize);
    }
}
