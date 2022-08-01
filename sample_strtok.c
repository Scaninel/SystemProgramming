#include <stdio.h>
#include <string.h>

int main (void)
{

    char s[]= "can,,***sevval,,,,*cihangir";

    char *pstr = NULL;

        pstr = strtok(s, ",*");
        puts(pstr);

        pstr = strtok(NULL, ",*");
        puts(pstr);

    return 0;
    
    
}
