/*Exercise 8-5. Modify the fsize program to print the other information contained in the inode 
entry.  */
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
/*output
name: ./ex4-14.c
   16104 bytes  links: 1  uid: 1000  gid: 1000  mode: 755  modified: Fri Dec 19 07:23:37 2025
name: ./ex1-14
     173 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Wed Dec 17 08:09:52 2025
name: ./ex1-9.c
     464 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Mon Dec 22 07:13:51 2025
name: ./ex1-20.c
    1453 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Wed Dec 31 14:30:19 2025
name: ./ex5-7.c
   16000 bytes  links: 1  uid: 1000  gid: 1000  mode: 755  modified: Tue Dec 16 07:45:40 2025
name: ./ex1-4
    1446 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Wed Dec 31 14:32:07 2025
name: ./ex5-8.c
   16248 bytes  links: 1  uid: 1000  gid: 1000  mode: 755  modified: Wed Dec 31 05:35:55 2025
name: ./ex5-1
     849 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Fri Dec 26 07:30:49 2025
name: ./ex3-5.c
     931 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Sun Dec 28 18:06:57 2025
name: ./ex4-3-2.c
     626 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Fri Dec 26 05:27:22 2025
name: ./ex3-2.c
     843 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Tue Dec 30 14:26:46 2025
name: ./ex5-4.c
   16176 bytes  links: 1  uid: 1000  gid: 1000  mode: 755  modified: Mon Jan 19 19:16:25 2026
name: ./ex8-1
     436 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Fri Dec 19 07:31:45 2025
name: ./ex1-14.c
   16040 bytes  links: 1  uid: 1000  gid: 1000  mode: 755  modified: Wed Dec 31 05:36:06 2025
name: ./ex5-3
    2622 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Mon Jan 19 14:36:37 2026
name: ./ex8-8.c
     955 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Mon Dec 29 10:43:48 2025
name: ./main.c
   16136 bytes  links: 1  uid: 1000  gid: 1000  mode: 755  modified: Mon Dec 22 13:28:47 2025
name: ./ex2-4
    1454 bytes  links: 1  uid: 1000  gid: 1000  mode: 644  modified: Wed Dec 31 14:33:52 2025
name: ./ex5-9.c
   16136 bytes  links: 1  uid: 1000  gid: 1000  mode: 755  modified: Tue Dec 23 18:13:37 2025
name: ./ex2-10
*/