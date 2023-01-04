#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_BUFFER_SIZE 512

void exit_sys(const char *msg);

int inFd, destFd;
int blockSize;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("at least 2 argument is required !!\n");
        exit(EXIT_FAILURE);
    }

    char *ifPos = strstr(argv[1], "if=");
    char *ofPos = strstr(argv[2], "of=");
    char *bs = NULL;
    char *count = NULL;
    int cnt = 0;
    char *conv = NULL;
    int ucaseFlg, lcaseFlg, exclFlg = 0;

    if (argc > 3)
        bs = strstr(argv[3], "bs=");

    if (argc > 4)
        count = strstr(argv[4], "count=");

    if (argc > 5)
        conv = strstr(argv[5], "conv=");

    if (ifPos == NULL || ofPos == NULL || ((ifPos - argv[1]) != 0) || ((ofPos - argv[2]) != 0))
    {
        printf("input and output file option must be entered correctly!!\n");
        exit(EXIT_FAILURE);
    }

    char *inputFileName = &argv[1][3];
    char *destFileName = &argv[2][3];

    if ((argc < 3) || (bs == NULL) || ((bs - argv[3]) != 0))
    {
        printf("block size is defined as 512 bytes as default\n");
        blockSize = 512;
    }
    else
    {
        blockSize = atoi(&argv[3][3]);
        printf("block size is defined by user as '%d-bytes'\n", blockSize);
    }

    if ((argc < 4) || (count == NULL) || ((count - argv[4]) != 0))
    {
        printf("block count is not defined, whole file is going to be copied\n");
    }
    else
    {
        cnt = atoi(&argv[4][6]);
        printf("block count is defined by user as '%d-bytes'\n", cnt);
    }

    if ((argc < 5) || (conv == NULL) || ((conv - argv[5]) != 0))
    {
        printf("no conversion option\n");
    }
    else
    {
        char *convStr = strtok(&conv[5], ",");

        while (convStr != NULL)
        {
            if (!strcmp(convStr, "ucase"))
            {
                printf("ucase option is used\n");
                ucaseFlg = 1;
            }
            if (!strcmp(convStr, "lcase"))
            {
                printf("lcase option is used\n");
                lcaseFlg = 1;
            }
            if (!strcmp(convStr, "excl"))
            {
                printf("excl option is used\n");
                exclFlg = 1;
            }

            convStr = strtok(NULL, ",");
        }

        if (!(ucaseFlg || lcaseFlg || exclFlg))
        {
            exit_sys("invalid conv option!!!!\n");
        }
    }

    // if ((strstr(inputFileName, " ") != NULL) || (strstr(destFileName, " ") != NULL))
    // {
    //     printf("file name can not contain ant SPACE!!\n");
    //     exit(EXIT_FAILURE);
    // }

    printf("input file name: %s\n", inputFileName);
    printf("destination file name: %s\n", destFileName);

    if ((inFd = open(inputFileName, O_RDONLY)) == -1)
        exit_sys(argv[1]);

    if ((destFd = open(destFileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        exit_sys(argv[2]);

    char *readBuf = malloc(blockSize);
    if (readBuf == NULL)
        exit_sys("insufficent memory for read buffer\n");

    int f_readSize = -1;

    do
    {
        f_readSize = read(inFd, readBuf, blockSize);
        if ((f_readSize <= 0) || (((argc < 4) || (count == NULL) || ((count - argv[3]) != 0)) && (cnt <= 0)))
            break;

        if (lcaseFlg)
        {
            for (int i = 0; i < f_readSize; i++)
            {
                if (readBuf[i] >= 'A' && readBuf[i] <= 'Z')
                {
                    readBuf[i] = readBuf[i] + 32;
                }
            }
            write(destFd, readBuf, f_readSize);
        }
        else if (ucaseFlg)
        {
            for (int i = 0; i < f_readSize; i++)
            {
                if (readBuf[i] >= 'a' && readBuf[i] <= 'z')
                {
                    readBuf[i] = readBuf[i] - 32;
                }
            }
            write(destFd, readBuf, f_readSize);
        }
        else
            write(destFd, readBuf, f_readSize);

        memset(readBuf, 0, blockSize);
    } while (f_readSize > 0, cnt--);

    printf("source file: \"%s\" coppied to ---> \"%s\" successfully !!\n", inputFileName, destFileName);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}