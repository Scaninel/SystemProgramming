#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define LINK_AT

void exit_sys(const char *msg);

int main(void)
{

#ifdef LINK_AT

    // if (argc != 6)
    // {
    //     fprintf(stderr, "wrong number of arguments!..\n");
    //     exit(EXIT_FAILURE);
    // }

    int fd;

    if ((fd = open("split.c", O_RDONLY)) == -1)
        exit_sys("split.c");

    int fdNew;

    if (linkat(fd, -100, fdNew, "../Sources", 0) == -1)
        exit_sys("link");

        // if (linkat(fd, argv[2], (const char*)argv[3], argv[4], 0) == -1)
        //     exit_sys("link");

#else
    if (argc != 3)
    {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if (link(argv[1], argv[2]) == -1)
        exit_sys("link");

    return 0;

#endif
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}