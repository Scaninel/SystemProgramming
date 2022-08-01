#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split (const char *str, const char *delim);

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

char **split (const char *str, const char *delim)
{
    char *s, *news, * newstr;
    char **tokens = NULL, **temp;
    int i;

    if((newstr = (char *) malloc(strlen(str) + 1) == NULL))
        return NULL;

    strcpy(newstr, str);

    for(i =0, s = strtok(newstr, delim); s != NULL; s = strtok(NULL, delim), ++i)
    {
        if((temp = (char**)realloc(tokens, sizeof(char *) * (i + 2))) == NULL)
        {
            free(newstr);
            free(tokens);
            return NULL;
        }

        tokens = temp;

        if((news = (char *)malloc(strlen(s) + 1)) == NULL)
        {
            free(newstr);
            free(tokens);
            return NULL;
        }

        strcpy(news, s);
        tokens[i] = news;
    }

    tokens[i] = NULL;

    free(newstr);

    return tokens;


}
