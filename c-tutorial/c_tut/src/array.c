/* Christopher Valencia
 * c tutorial
*/
#include <stdio.h>

#define MAX_NUM_OF_CELLS 128

int main(void) {
    int numDoubles = 0;
    double number[MAX_NUM_OF_CELLS];
    double sum = 0.0, average = 0.0;

    printf("Provide a desired number of doubles? \n");
    scanf( "%d", &numDoubles);

    printf("Enter doubles: \n");
    for(int index = 0; index < numDoubles; index++)
    {
        scanf("%lf", &number[index]);
    }

    printf("Data: ");
    for(int index = 0; index < numDoubles; index++)
    {
        printf("%0.1lf ", number[index]);
        sum += number[index];
    }
    average = sum / numDoubles;
    printf("\nAverage: %0.1lf\n", average);

    /*for (int index = 0; index < MAX_NUM_OF_CELLS; index++) {
        number[index] = index;
    }
    /* now, number[index]=index; will cause error: why ?

    for (int index = 0; index < MAX_NUM_OF_CELLS; index = index + 1) {
        sum += number[index];  /* sum array elements
    }

    printf("sum = %d\n", sum);*/

    return 0;
}
