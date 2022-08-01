#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split (char *str, const char *delim);

int main(void)
{
    char names[] = "can, şevval, cihangir";
    char **str;
    int i;

    if((str = split(names, ", ")) == NULL)
    {
        fprintf(stderr, "cannot split!..\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; str[i] != NULL; ++i)
    {
        puts(str[i]);
    }

    free(str);

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
