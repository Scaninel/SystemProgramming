    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    char **split (char *str, const char *delim);

    int main (int argc, char *argv[])
    {
        char **str = NULL;
        char *inFileName = NULL;
        char *outFileName = NULL;

        int bs=0;
        int count=0;

        for (int i=0; i<argc; i++)
        {
            printf("arg-%d: %s\n", i, argv[i]);

            if((str = split(argv[i], "=")) == NULL)
            {
                fprintf(stderr, "cannot split!..\n");
                exit(EXIT_FAILURE);
            }

            switch (i)
            {
            case 1:
            {
                if(strcmp(str[0], "if"))
                {
                    fprintf(stderr, "wrong 1st arg!..\n");
                    exit(EXIT_FAILURE); 
                }

                inFileName = str[1];
                printf("input filename:%s\n", inFileName);
                break;
            }
            case 2:
            {
                if(strcmp(str[0], "of"))
                {
                    fprintf(stderr, "wrong 2nd arg!..\n");
                    exit(EXIT_FAILURE);
                }

                outFileName= str[1];
                printf("output filename:%s\n", outFileName);
                break;
            }
            case 3:
            {
                if(strcmp(str[0], "bs"))
                {
                    fprintf(stderr, "wrong 3rd arg!..\n");
                    exit(EXIT_FAILURE);
                }
                /*3rd arg process*/
                for (int ndx=0; ndx<strlen(str[1]); ndx++)
                {
                    if (!isdigit(str[1][ndx])) 
                    {
                        fprintf(stderr, "wrong 3rd arg value!..\n");
                        exit(EXIT_FAILURE);
                    }
                }

                bs = atoi(str[1]);
                printf("block size:%d\n",bs);


                break;
            }
            case 4:
            {
                if(strcmp(str[0], "count"))
                {
                    fprintf(stderr, "wrong 4th arg!..\n");
                    exit(EXIT_FAILURE);
                }
                /*4th arg process*/
                for (int ndx=0; ndx<strlen(str[1]); ndx++)
                {
                    if (!isdigit(str[1][ndx])) 
                    {
                        fprintf(stderr, "wrong 4th arg value!..\n");
                        exit(EXIT_FAILURE);
                    }
                }

                count = atoi(str[1]);
                printf("block count:%d\n",count);

                break;
            }
            case 5:
            {
                if(strcmp(str[0], "conv"))
                {
                    fprintf(stderr, "wrong 5th arg!..\n");
                    exit(EXIT_FAILURE);
                }
                
                if(!(!strcmp(str[1], "ucase") || !strcmp(str[1], "lcase") || !strcmp(str[1], "excl")))
                {
                    fprintf(stderr, "wrong 5th arg value!..\n");
                    exit(EXIT_FAILURE);
                }
                /*5th arg process*/
                
                break;
            }
            
            default:
                break;
            }

            free(str);
        }



        




        // char names[] = "can, şevval, cihangir";
        // char **str;
        // int i;

        // if((str = split(names, ", ")) == NULL)
        // {
        //     fprintf(stderr, "cannot split!..\n");
        //     exit(EXIT_FAILURE);
        // }

        // for(i = 0; str[i] != NULL; ++i)
        // {
        //     puts(str[i]);
        // }

        // free(str);

    }

    char **split (char *str, const char *delim)
    {
        char *s;
        char **tokens = NULL, **temp;
        int i;

        for(i =0, s = strtok(str, delim); s != NULL; s = strtok(NULL, delim), ++i)
        {
            if((temp = (char**)realloc(tokens, sizeof(char *) * (i + 2))) == NULL)
            {
                free(tokens);
                return NULL;
            }

            tokens = temp;
            tokens[i] = s;
        }

        tokens[i] = NULL;

        return tokens;


    }