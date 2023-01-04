#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

int callback(const char *path, const struct stat *finfo, int flag, struct FTW *ftw);
void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if ((result = nftw(argv[1], callback, 100, FTW_PHYS)) == -1)
        exit_sys("nftw");

    printf("result = %d\n", result);

	return 0;
} 

int callback(const char *path, const struct stat *finfo, int flag, struct FTW *ftw)
{
    switch (flag) {
        case FTW_DNR:
            printf("%*s%s (cannot read directory)\n", ftw->level * 4, "", path + ftw->base);        
            break;
        case FTW_NS:
            printf("%*s%s (cannot get statinfo)\n", ftw->level * 4, "", path + ftw->base);        
            break;
        default:
            printf("%*s%s\n", ftw->level * 4, "", path + ftw->base);
    }
    
    return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}