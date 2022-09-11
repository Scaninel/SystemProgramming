#include <stdio.h>
 
int tar (double a)
{
    printf("function tar, val: %f\n", a);
    return 0;
}

int (*bar(double a))(double)
{
    printf("function bar, val: %f\n", a);
    return tar;
}

int(*(*foo(void))(double))(double)
{
    printf("function foo\n");
    return bar;
}

 int main(void)
 {
    int (*(*pf1)(double))(double);

    pf1 = foo();

    int (*pf2)(double);

    pf2 = pf1(47.5);
    pf2(74.5);

    return 0;
 }