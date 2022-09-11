#include <stdio.h>
/*---------------SECTION_1--------------------------*/
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

/*-----------------SECTION_2------------------------*/
int bar (double a)
{
    printf("function bar: %f\n", a);

    return 0;
}

int (*foo(void)) (double)
{
    return bar;
}
/*--------------SECTION_3---------------------------*/
/*typedef declaration*/
typedef int (*PF) (double);

PF tdFoo (void)
{
    return bar;
}
/*END*//*typedef declaration*/
/*------------SECTION_4-----------------------------*/
int tar2(long a)
{
    printf("function tar2\n");
    return 0;
}

int (*bar2(double a))(long)
{
    printf("function bar2\n");
    return tar2;
}

int(*(*car(void))(double))(long)
{
    printf("function car\n");
    return bar2;
}
/*-----------------------------------------*/

int main(void)
{
    /*---------------SECTION_2--------------------------*/
    int (*pfs[4])(void);

    pfs[0] = foo1;
    pfs[1] = foo2;
    pfs[2] = foo3;
    pfs[3] = foo4;

    for (int i = 0; i < 4; i++)
    {
        pfs[i]();
    }
    /*---------------SECTION_2--------------------------*/

    int (*pf)(double);

    pf = foo();

    pf(4.7);
/*---------------SECTION_3--------------------------*/
/*typedef declaration*/
    PF tdPf;

    tdPf = tdFoo();

    tdPf(4.7);
/*END*/
/*---------------SECTION_4--------------------------*/
    int (*(*pf1)(double))(long);

    pf1 = car(); 

    int (*pf2)(long);

    pf2 = pf1(0);
    pf2(0);

    return 0;
}