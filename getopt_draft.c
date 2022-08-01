#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char *argv[])
{
    int result;
    int flagA, flagB, flagC;

    flagA = flagB = flagC = 0;
    char *argB;
    char *argC;

    int i=0;
    opterr = 0;
    int errFlag =0;

    while((result = getopt(argc, argv, "ab:c:")) != -1)
    {
        switch (result) 
        {
            case 'a':
            {
                flagA=1;
                break;
            }
            
            case 'b':
            {
                flagB=1;
                argB = optarg;
                break;
            }
            case 'c':
            {
                flagC=1;
                argC = optarg;
                break;
            }
            case '?':
            {
                fprintf(stderr, "invalid option: -%c\n", optopt);
                errFlag=1;
                break;
            }

            default:
            {

                break;
            }
        }
    }

    if(errFlag)
      exit(EXIT_FAILURE);  

    if(flagA)
        printf("-a option is used\n");

    if(flagB)
        printf("-b option is used wtih arg: %s\n", argB);

    if(flagC)
        printf("-c option is used wtih arg: %s\n", argC);


    if(optind != argc)      // eğer hiçbir argümansız seçenek kullanılmamışsa optind argc ye eşit olur
    {
        for(i = optind; i<argc; i++)
        {
            printf("seçeneksiz argüman, %s\n", argv[i]);
        }

    }

    return 0;
}
