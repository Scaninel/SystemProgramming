#include <stdio.h>

int foo1(void)
{
    printf("foo1\n");
    return 0;
}

int foo2(void)
{
    printf("foo2\n");
    return 0;
}
int foo3(void)
{
    printf("foo3\n");
    return 0;
}
int foo4(void)
{
    printf("foo4\n");
    return 0;
}

int main(void)
{

    int (*pfs[4])(void);

    pfs[0] = foo1;
    pfs[1] = foo2;
    pfs[2] = foo3;
    pfs[3] = foo4;

    for (int i = 0; i < 4; i++)
    {
        pfs[i]();
    }

    return 0;
}