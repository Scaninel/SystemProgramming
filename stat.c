#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

void exit_sys(const char *msg);
void disp_mode(mode_t mode);

int main(int argc, char *argv[])
{
    struct stat finfo;
    struct tm *pt;

    if (argc == 1) {
        fprintf(stderr, "file(s) must be specified!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; ++i) {
        if (stat(argv[i], &finfo) == -1)
            exit_sys("stat");

        printf("i-node no: %llu\n", (unsigned long long)finfo.st_ino);
        printf("file mode: ");
        disp_mode(finfo.st_mode);
        printf("number of hard links: %llu\n", (unsigned long long)finfo.st_nlink);
        printf("user id: %llu\n", (unsigned long long)finfo.st_uid);
        printf("group id: %llu\n", (unsigned long long)finfo.st_gid);
        printf("file size: %lld\n", (long long)finfo.st_size);
        printf("file block size: %lld\n", (long long)finfo.st_blksize);
        printf("number of blocks: %lld\n", (long long)finfo.st_blocks);

        pt = localtime(&finfo.st_mtim.tv_sec);
        printf("last modification: %02d/%02d/%04d %02d:%02d:%02d\n", pt->tm_mday, pt->tm_mon + 1, pt->tm_year + 1900, 
                    pt->tm_hour, pt->tm_min, pt->tm_sec);
        pt = localtime(&finfo.st_atim.tv_sec);
        printf("last access (read): %02d/%02d/%04d %02d:%02d:%02d\n", pt->tm_mday, pt->tm_mon + 1, pt->tm_year + 1900, 
                    pt->tm_hour, pt->tm_min, pt->tm_sec);
        pt = localtime(&finfo.st_ctim.tv_sec);
        printf("last i-node changed: %02d/%02d/%04d %02d:%02d:%02d\n", pt->tm_mday, pt->tm_mon + 1, pt->tm_year + 1900, 
                    pt->tm_hour, pt->tm_min, pt->tm_sec);
        
        if (argc > 2)
            printf("-----------------\n");
    }

	return 0;
} 

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}

void disp_mode(mode_t mode)
{
    static mode_t modes[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    static mode_t ftypes[] = {S_IFBLK, S_IFCHR, S_IFIFO, S_IFREG, S_IFDIR, S_IFLNK, S_IFSOCK};

    for (int i = 0; i < 7; ++i)
        if ((mode & S_IFMT) == ftypes[i]) {
            putchar("bcp-dls"[i]);
            break;
        }
    /* 
    
    alternatifi 
    
    if (S_ISBLK(mode))
        putchar('b');
    else if (S_ISCHR(mode))
        putchar('c');
    else if (S_ISDIR(mode))
        putchar('d');
    else if (S_ISFIFO(mode))
        putchar('p');
    else if (S_ISREG(mode))
        putchar('-')
    else if (S_ISLNK(mode))
        putchar('l');
    else if (S_ISSOCK(mode))
        putchar('s');
    else 
        putchar('?');
    
    */ 

    for (int i = 0; i < 9; ++i)
         putchar(mode & modes[i] ? "rwx"[i % 3] : '-');
    putchar('\n');    
}