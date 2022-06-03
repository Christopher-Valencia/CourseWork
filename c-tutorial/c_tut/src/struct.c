#include <stdio.h>
#include <person.h>
#include <stdlib.h>

struct birthday {
    int month;
    int day;
    int year;
};

int main(void)
{

    int numberOfEmployees;
    printf("How many employees?\n");
    (void)scanf("%d", &numberOfEmployees);

    PERSON *employees[numberOfEmployees];

    for(int y=0; y<numberOfEmployees; y++)
    {
        employees[y] = (PERSON *) malloc(sizeof(PERSON));
    }

    for(int x=0; x<numberOfEmployees; x++)
    {
        addEmployee(employees[x]);
    }

    displayAllEmployees(employees, numberOfEmployees);

    /*
    struct birthday myBday;    // - no ‘new’ needed !
                               // then, use dot notation like in Java !
    scanf("%d/%d/%d", &myBday.month, &myBday.day, &myBday.year);
    printf("I was born on %d/%d/%d\n", myBday.month, myBday.day, myBday.year);
     */

    return 0;
}
