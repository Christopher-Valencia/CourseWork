#include <stdio.h>

int main(void) {

    int j = 1;  // what is j now?

    int *ptr = &j; /* initialize ptr before using it */
    printf("%d \n", j);

    *ptr = 4;   // what is j now?
    printf("%d \n", j);

    j = *ptr;   // what is j now?
    printf("%d \n", j);

    return 0;
}
