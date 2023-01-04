#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void walkdir(const char *path, int level);
void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    walkdir(argv[1], 0);

    

    return 0;
}

void walkdir(const char *path, int level)
{
    DIR *dir;
    struct dirent *de;
    struct stat finfo;

    if ((dir = opendir(path)) == NULL)
    {
        fprintf(stderr, "cannot read directory: %s\n", path);
        return;
    }

    if (chdir(path) == -1)
    {
        fprintf(stderr, "directory cannot change: %s\n", path);
        goto EXIT;
    }

    while (errno = 0, (de = readdir(dir)) != NULL)
    {
        printf("%*s%s\n", level * 4, "", de->d_name);
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;
        if (lstat(de->d_name, &finfo) == -1)
        {
            fprintf(stderr, "cannot get stat info: %s\n", de->d_name);
            continue;
        }

        if (S_ISDIR(finfo.st_mode))
        {
            walkdir(de->d_name, level + 1);

            if (chdir("..") == -1)
            {
                fprintf(stderr, "directory cannot change: %s\n", path);
                goto EXIT;
            }

            if (rmdir(de->d_name) == 0)
                printf("<%*s%s> directory DELETED\n", level * 4, "", de->d_name);
            else
                fprintf(stderr, "directory %s cannot deleted\n", de->d_name);
        }
        else if (S_ISREG(finfo.st_mode))
        {

            if (remove(de->d_name) == 0)
                printf("\"%*s%s\" regular file DELETED\n", level * 4, "", de->d_name);
            else
                fprintf(stderr, "file %s cannot deleted\n", de->d_name);
        }
    }
    if (errno != 0)
        fprintf(stderr, "cannot read directory info: %s\n", path);

EXIT:
    closedir(dir);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
