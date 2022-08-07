#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

#define DEFAULT_LINE_NUMBER 10

int main(int argc, char *argv[])
{
    int result, index;
    int bytes_flag, lines_flag, verbose_flag, help_flag, version_flag;
    char *bytes_arg, *lines_arg;

    int errFlag = 0;
    opterr = 0;

    bytes_flag = lines_flag = verbose_flag = help_flag = version_flag = 0;
    bytes_arg = lines_arg = NULL;

    char *inputFileName = NULL;

    struct option options[] = {
        {"bytes", required_argument, NULL, 'c'}, // "help" argümanın adı, "no_argument" seçenekli/seçeneksiz olması,
        {"lines", optional_argument, NULL, 'n'}, // 3.parametreye NULL geçilirse getopy_long argümanı bulursa 4. parametreye girilen değeri geri döner
        {"verbose", no_argument, &verbose_flag, 'v'},
        {"help", no_argument, &help_flag, 3},    // 3.parametreye bir adres girilirse ör: &helpFlg, getopt_long eğer argümanı bulursa helpFlg'yi
        {"version", no_argument, &version_flag, 4},
        {0, 0, 0, 0}, // 4. parametredeki değer ile set eder
    };

    while ((result = getopt_long(argc, argv, "c:n:v", options, &index)) != -1)
    {
        switch (result)
        {
        case 'c':
        {
            bytes_flag = 1;
            bytes_arg = optarg;
            break;
        }
        case 'n':
        {
            lines_flag = 1;
            lines_arg = optarg;
            break;
        }
        case 'v':
        {
            verbose_flag = 1;
            break;
        }

        case '?':
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

    if (optind != argc)
    {
        inputFileName = argv[optind];
        printf("input file name: %s\n", inputFileName);
    }
    else
    {
        if (!help_flag)
        {
            printf("NO INPUT FILE NAME\n");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_flag)
    {
        printf("-c or --bytes option is used\n");
        static int c = 0;

        FILE *fp = fopen(inputFileName, "r");

        if (!fp)
        {
            perror("File opening failed");
            exit(EXIT_FAILURE);
        }
        printf("bytes arg: %s", bytes_arg);

        int inputBytes = atoi(bytes_arg);
        printf("input bytes: %d\n", inputBytes);

        for (int i = 0; i < inputBytes; ++i)
        {
            c = fgetc(fp);
            if (feof(fp))
                break;
            putchar(c);
        }
        putchar('\n');
        fclose(fp);
    }

    if (lines_flag)
    {
        if (lines_arg == NULL) /*write 10 line by default*/
        {
            printf("-n option is used with default line number\n");
            static int c = 0;

            FILE *fp = fopen(inputFileName, "r");

            if (!fp)
            {
                perror("File opening failed");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < DEFAULT_LINE_NUMBER; ++i)
            {
                while ((c = fgetc(fp)) != '\n')
                {
                    if (feof(fp))
                        break;
                    putchar(c);
                }
                putchar('\n');
            }
            putchar('\n');
            fclose(fp);
        }
        else
        {
            printf("input lines argument %s", lines_arg);
            int inputLines = atoi(lines_arg);

            printf("-n option is used\n");
            static int c = 0;

            FILE *fp = fopen(inputFileName, "r");

            if (!fp)
            {
                perror("File opening failed");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < inputLines; ++i)
            {
                while ((c = fgetc(fp)) != '\n')
                {
                    putchar(c);
                }
                putchar('\n');
            }
            putchar('\n');
            fclose(fp);
        }
    }

    if (verbose_flag)
    {
        printf("==>%s<==\n", inputFileName);
        static int c = 0;

        FILE *fp = fopen(inputFileName, "r");

        if (!fp)
        {
            perror("File opening failed");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < DEFAULT_LINE_NUMBER; ++i)
        {
            while ((c = fgetc(fp)) != '\n')
            {
                putchar(c);
            }
            putchar('\n');
        }
        putchar('\n');
        fclose(fp);
    }

    if (help_flag)
    {
        printf("sage: head [OPTION]... [FILE]... \n\
Print the first 10 lines of each FILE to standard output.\n\
With more than one FILE, precede each with a header giving the file name.\n\
\n\
With no FILE, or when FILE is -, read standard input.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -c, --bytes=[-]NUM       print the first NUM bytes of each file;\n\
                             with the leading '-', print all but the last\n\
                             NUM bytes of each file\n\
  -n, --lines=[-]NUM       print the first NUM lines instead of the first 10;\n\
                             with the leading '-', print all but the last\n\
                             NUM lines of each file\n\
  -v, --verbose            always print headers giving file names\n\
      --help     display this help and exit\n\
      --version  output version information and exit\n");
    }

    if (version_flag)
    {
        printf("head version 1.0 \nWritten by S.Can İNEL, on July 2022\nDedicated to my sweetheart Ms.Şevval :)\n");
    }

    return 0;
}
