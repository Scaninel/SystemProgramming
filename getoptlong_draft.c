#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int main (int argc, char *argv[])
{
    int result, index;
    int a_flag, b_flag, c_flag, help_flag, count_flag, line_flag;
    char *b_arg, *count_arg, *line_arg;

    int i=0;
    int errFlag = 0;
    opterr = 0;

    a_flag = b_flag = c_flag = help_flag = count_flag = line_flag =0;
    b_arg = count_arg = line_arg = NULL;

    struct option options [] ={
        {"help", no_argument, &help_flag, 1},              // "help" argümanın adı, "no_argument" seçenekli/seçeneksiz olması,
        {"count", required_argument, NULL, 2},      // 3.parametreye NULL geçilirse getopy_long argümanı bulursa 4. parametreye girilen değeri geri döner
        {"line", optional_argument, NULL, 3},       // 3.parametreye bir adres girilirse ör: &helpFlg, getopt_long eğer argümanı bulursa helpFlg'yi 
        {0,0,0,0},                                  // 4. parametredeki değer ile set eder
    };

    while((result = getopt_long(argc, argv, "ab:c:", options, &index)) != -1)
    {
        switch (result) 
        {
            case 'a':         
            {
                a_flag =1;
                break;
            }
            case 'b':         
            {
                b_flag =1;
                b_arg = optarg;
                break;
            }
            case 'c':        
            {
                c_flag =1;
                break;
            }
            case 2:        
            {
                count_flag =1;
                count_arg = optarg;
                break;
            }
            case 3:        
            {
                line_flag =1;


                line_arg = optarg;
                break;
            }

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

    if(a_flag)
        printf("-a option is used\n");

    if(b_flag)
        printf("-b option is used with arg: \"%s\"...\n", b_arg);

    if(c_flag)
        printf("-c option is used \n");

    if(help_flag)
        printf("--help option is used \n");

    if(count_flag)
        printf("--count option is used with arg: \"%s\"...\n", count_arg);

    if(line_flag)
    {
        if(line_arg != NULL)
            printf("--line option is used with arg: \"%s\"...\n", line_arg);
        else
            printf("--line option is used without argument...\n");
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
