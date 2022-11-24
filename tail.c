#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int main (int argc, char *argv[])
{
    int result, index;
    int c_flag, n_flag, v_flag, version_flag, help_flag;
    char *byte_arg, *line_arg;

    int i=0;
    int errFlag = 0;
    opterr = 0;

    c_flag = n_flag = v_flag = version_flag = help_flag = 0;
    byte_arg = line_arg = NULL;

    struct option options [] ={
        {"bytes", no_argument, &c_flag, 1},              // "help" argümanın adı, "no_argument" seçenekli/seçeneksiz olması,
        {"lines", required_argument, &n_flag, 1},      // 3.parametreye NULL geçilirse getopy_long argümanı bulursa 4. parametreye girilen değeri geri döner
        {"verbose", no_argument, &v_flag, 1},       // 3.parametreye bir adres girilirse ör: &helpFlg, getopt_long eğer argümanı bulursa helpFlg'yi 
        {"version", no_argument, &version_flag, 1},
        {"help", no_argument, &help_flag, 1},
        {0,0,0,0},                                  // 4. parametredeki değer ile set eder
    };

    while((result = getopt_long(argc, argv, "c:n:v", options, &index)) != -1)
    {
        switch (result) 
        {
            case 'c':         
            {
                c_flag =1;
                byte_arg = optarg;;
                break;
            }
            case 'n':         
            {
                n_flag =1;
                line_arg = optarg;
                break;
            }
            case 'v':        
            {
                v_flag =1;
                break;
            }
            // case 2:        
            // {
            //     count_flag =1;
            //     break;
            // }
            // case 3:        
            // {
            //     line_flag =1;
            //     break;
            // }

            case '?':
            {
                if(optopt == 'b')
                    fprintf(stderr, "-b option must have an argument\n");
                else if(optopt == 2)
                    fprintf(stderr, "argument must be specified with count option \n");
                else if (optopt !=0)
                    fprintf(stderr, "invalid option: -%c\n", optopt);
                else
                    fprintf(stderr, "invalid long option...\n");
                
                errFlag=1;
                break;
            }
        }
    }

    if(errFlag)
      exit(EXIT_FAILURE);  

    if(c_flag)
        printf("-c option is used\n");

    if(n_flag)
        printf("-n option is used with arg: \"%s\"...\n", line_arg);

    if(v_flag)
        printf("-v option is used \n");

    // if(count_flag)
    //     printf("--count option is used with arg: \"%s\"...\n", count_arg);

    // if(line_flag)
    // {
    //     if(line_arg != NULL)
    //         printf("--line option is used with arg: \"%s\"...\n", line_arg);
    //     else
    //         printf("--line option is used without argument...\n");
    // }

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
    }

    if (version_flag)
    {
        printf("tail version 1.0 \nWritten by S.Can İNEL, on July 2022\nDedicated to my sweetheart Ms.Şevval :)\n");
    }

    if(optind != argc)
    {
        printf("seceneksiz (yani normal) argumanlar\n");

        for(i = optind; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
    }

    return 0;
}
