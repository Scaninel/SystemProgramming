#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define DEFAULT_BUFFER_SIZE 512

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int inFd, destFd;

    if (argc < 2)
    {
        printf("at least 2 argument is required !!\n");
        exit(EXIT_FAILURE);
    }

    char *ifPos = strstr(argv[1], "if=");
    char *ofPos = strstr(argv[2], "of=");

    if (ifPos == NULL || ofPos == NULL || ((ifPos - argv[1]) != 0) || ((ofPos - argv[2]) != 0))
    {
        printf("input and output file option must be entered correctly!!\n");
        exit(EXIT_FAILURE);
    }

    char *inputFileName = &argv[1][3];
    char *destFileName = &argv[2][3];

    // if ((strstr(inputFileName, " ") != NULL) || (strstr(destFileName, " ") != NULL))
    // {
    //     printf("file name can not contain ant SPACE!!\n");
    //     exit(EXIT_FAILURE);
    // }

    printf("input file name: %s\n", inputFileName);
    printf("destination file name: %s\n", destFileName);

    if ((inFd = open(inputFileName, O_RDONLY)) == -1)
        exit_sys(argv[1]);

    if ((destFd = open(destFileName, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)
        exit_sys(argv[2]);



    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}