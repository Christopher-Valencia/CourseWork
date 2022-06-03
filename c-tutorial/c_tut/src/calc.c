//
// Created by Chris on 9/9/2020.
//

#include <stdio.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void add(int, int);
void sub(int, int);
void multi(int, int);
void div(int, int);

void calc(void (*)(int, int), int, int);

int main(void)
{
    int op1, op2;
    char sym;

    while(1)
    {
        printf( "calc > ");
        scanf( "%d %c %d", &op1, &sym, &op2);
        //printf( "%d\n%c\n%d\n", op1, sym, op2);

        switch(sym)
        {
            case '+':
                calc(add, op1, op2);
                break;
            case '-':
                calc(sub, op1, op2);
                break;
            case '*':
                calc(multi, op1, op2);
                break;
            case '/':
                calc(div, op1, op2);
                break;
        }
    }

    return (0);
}

void calc(void (*f)(int, int), int param1, int param2)
{
    (*f)(param1, param2);
}

void add(int x, int y)
{
    printf("%d\n", x+y);
}

void sub(int x, int y)
{
    printf("%d\n", x-y);
}

void multi(int x, int y)
{
    printf("%d\n", x*y);
}

void div(int x, int y)
{
    printf("%d\n", x/y);
}
#pragma clang diagnostic pop