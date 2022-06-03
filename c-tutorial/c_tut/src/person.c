/*
// Created by Chris Valencia on 9/16/2020.
*/

#include <stdio.h>
#include <person.h>

//populates an element in array of PERSON from inputs
void addEmployee(PERSON *employee)
{
    printf("Enter information for the next employee.\n");
    printf("Name : ");
    scanf(" %[^\n]", employee->name);
    //printf( "\n%s : \n", employee->name);
    printf("Age : ");
    (void)scanf("%d", &employee->age);
    printf("Height : ");
    (void)scanf( "%f", &employee->height);
    printf( "Birthday (MM / DD / YYYY ) : ");
    (void)scanf( "%d / %d / %d", &employee->bday.month, &employee->bday.day, &employee->bday.year);
}

//displays the information of an employee in a readable format
void displayEmployee(PERSON *employee)
{
    printf( "\n%s : \n", employee->name);
    printf( "\tAge : %d", employee->age);
    printf( "\tHeight : %.2f", employee->height);
    printf( "\tBirthday : %d/%d/%d\n", employee->bday.month, employee->bday.day, employee->bday.year);
}

//displays all employees information readably
void displayAllEmployees(PERSON *employees[], int numberOfEmployees)
{
    printf("\nDisplaying Employees...\n");
    for(int x=0; x<numberOfEmployees; x++)
    {
        displayEmployee(employees[x]);
    }
}

