#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define DEFAULT_LINE_NUMBER 10

int main(int argc, char *argv[])
{
    int result, index;
    int verbose_flag, version_flag, help_flag, bytes_flag, lines_flag;
    char *byte_arg, *line_arg;

    int i = 0;
    int errFlag = 0;
    opterr = 0;

    verbose_flag = version_flag = help_flag = bytes_flag = lines_flag = 0;
    byte_arg = line_arg = NULL;

    char *inputFileName = NULL;

    struct option options[] = {
        {"bytes", required_argument, NULL, 'c'}, // "help" argümanın adı, "no_argument" seçenekli/seçeneksiz olması,
        {"lines", required_argument, NULL, 'n'}, // 3.parametreye NULL geçilirse getopy_long argümanı bulursa 4. parametreye girilen değeri geri döner
        {"verbose", no_argument, &verbose_flag, 'v'},  // 3.parametreye bir adres girilirse ör: &helpFlg, getopt_long eğer argümanı bulursa helpFlg'yi 4. parametredeki değer ile set eder
        {"version", no_argument, &version_flag, 1},
        {"help", no_argument, &help_flag, 1},
        {0, 0, 0, 0},
    };

    while ((result = getopt_long(argc, argv, "c:n:v", options, &index)) != -1)
    {
        switch (result)
        {
        case 'c':
        {
            bytes_flag = 1;
            byte_arg = optarg;
            break;
        }
        case 'n':
        {
            lines_flag = 1;
            line_arg = optarg;
            break;
        }
        case 'v':
        {
            verbose_flag = 1;
            break;
        }

        case '?': // hata durumunda getopt_long "?" geri döner
        {
            if (optopt == 'c')
                fprintf(stderr, "-c option must have an argument\n");
            else if (optopt == 'n')
                fprintf(stderr, "-n option must have an argument\n");
            else if (optopt != 0)
                fprintf(stderr, "invalid option: -%c\n", optopt);
            else
                fprintf(stderr, "invalid long option...\n");

            errFlag = 1;
            break;
        }
        }
    }

    if (errFlag)
        exit(EXIT_FAILURE);

    if (optind != argc) // seçeneksiz argüman
    {
        inputFileName = argv[optind];
        // printf("input file name: %s\n", inputFileName);
    }
    else
    {
        if (!help_flag && !version_flag)
        {
            printf("NO INPUT FILE NAME, stdin is used as input\n");
            inputFileName = NULL;
            // exit(EXIT_FAILURE);
        }
    }

    if (verbose_flag)
        printf("===============================\nfile \"%s\" is written as below\n===============================\n\n", inputFileName);

    if (help_flag)
    {
        printf("Usage: tail [OPTION]... [FILE]...\n\
Print the last 10 lines of each FILE to standard output.\n\
With more than one FILE, precede each with a header giving the file name.\n\
\n\
With no FILE, or when FILE is -, read standard input.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -c, --bytes=[+]NUM       output the last NUM bytes; or use -c +NUM to\n\
                             output starting with byte NUM of each file\n\
  -f, --follow[={name|descriptor}]\n\
                           output appended data as the file grows;\n\
                             an absent option argument means 'descriptor'\n\
  -F                       same as --follow=name --retry\n\
  -n, --lines=[+]NUM       output the last NUM lines, instead of the last 10;\n\
                             or use -n +NUM to output starting with line NUM\n\
      --max-unchanged-stats=N\n\
                           with --follow=name, reopen a FILE which has not\n\
                             changed size after N (default 5) iterations\n\
                             to see if it has been unlinked or renamed\n\
                             (this is the usual case of rotated log files);\n\
                             with inotify, this option is rarely useful\n\
      --pid=PID            with -f, terminate after process ID, PID dies\n\
  -q, --quiet, --silent    never output headers giving file names\n\
      --retry              keep trying to open a file if it is inaccessible\n\
  -s, --sleep-interval=N   with -f, sleep for approximately N seconds\n\
                             (default 1.0) between iterations;\n\
                             with inotify and --pid=P, check process P at\n\
                             least once every N seconds\n\
  -v, --verbose            always output headers giving file names\n\
  -z, --zero-terminated    line delimiter is NUL, not newline\n\
      --help     display this help and exit\n\
      --version  output version information and exit\n");

    return 0;

    }

    if (version_flag)
    {
        printf("tail version 1.0 \nWritten by S.Can İNEL, on July 2022\nDedicated to my sweetheart Ms.Şevval :)\n");

        return 0;
    }

    if(bytes_flag && lines_flag)
    {
        printf("byte and line options cannot be used together\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = NULL;

    if (inputFileName == NULL || strcmp(inputFileName, "-") == 0)
    {
        fp = stdin;
    }
    else
    {
        fp = fopen(inputFileName, "r");
        if (fp == NULL)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }

    fseek(fp, 0, SEEK_END); // dosya göstericisini dosyanın sonuna konumlandırır

    if (bytes_flag)
    {
        int readRes = 0;
        char readByte = 0;
        int readCount = 0;

        do
        {
            fseek(fp, -2, SEEK_CUR);
            readRes = fread(&readByte, 1, 1, fp);
            readCount++;

        } while (readRes && ftell(fp) >= 2 && readCount < atoi(byte_arg));

        readByte = 0;

        fseek(fp, -1, SEEK_CUR);

        while (fread(&readByte, 1, 1, fp))
        {
            printf("%c", readByte);
        }
    }

    if (lines_flag)
    {

        int readRes = 0;
        char readByte = 0;
        int readLineCnt = 0;

        do
        {
            fseek(fp, -2, SEEK_CUR);
            readRes = fread(&readByte, 1, 1, fp);
            if (readByte == '\n')
                readLineCnt++;

        } while (readRes && ftell(fp) >= 2 && readLineCnt < atoi(line_arg));

        readByte = 0;

        fseek(fp, -1, SEEK_CUR);

        while (fread(&readByte, 1, 1, fp) && readLineCnt >= 0)
        {
            printf("%c", readByte);
            if (readByte == '\n')
                readLineCnt--;
        }
    }

    if (!bytes_flag && !lines_flag)
    {
        int readRes = 0;
        char readByte = 0;
        int readLineCnt = 0;

        do
        {
            fseek(fp, -2, SEEK_CUR);
            readRes = fread(&readByte, 1, 1, fp);
            if (readByte == '\n')
                readLineCnt++;

        } while (readRes && ftell(fp) >= 2 && readLineCnt < DEFAULT_LINE_NUMBER);

        readByte = 0;

        fseek(fp, -1, SEEK_CUR);

        while (fread(&readByte, 1, 1, fp) && readLineCnt >= 0)
        {
            printf("%c", readByte);
            if (readByte == '\n')
                readLineCnt--;
        }
    }
    return 0;
}
