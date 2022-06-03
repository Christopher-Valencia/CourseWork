#include <stdio.h>

void swapIntegers(int *, int *);
void swapStrings(char ** , char**);

int main(void) {
    int num1 = 5, num2 = 10;
    char *str1 = "Hello";
    char *str2 = "Goodbye";

    printf("Before the swap: num1 = %d and num2 = %d\n", num1, num2);
    swapIntegers(&num1, &num2);
    printf("After the swap: num1 = %d and num2 = %d\n", num1, num2);

    printf("Before swap: str1 = %s and str2 = %s\n", str1, str2);
    swapStrings(&str1, &str2);
    printf("After swap: str1 = %s and str2 = %s\n", str1, str2);

    return 0;
}

void swapStrings(char **s1, char **s2)
{
    char* temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void swapIntegers(int *n1, int *n2) { /* passed and returned by using values of pointers */
    int temp;

    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
