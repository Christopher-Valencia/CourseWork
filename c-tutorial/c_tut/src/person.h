//
// Created by Chris Valencia on 9/16/2020.
//

#ifndef PERSON_H_
#define PERSON_H_

typedef char NAME[41];

typedef struct date {
    int month;
    int day;
    int year;
} DATE;

typedef struct person {
    NAME name;
    int age;
    float height;
    DATE bday;
} PERSON;

void addEmployee(PERSON *employee);//populates an element in array of PERSON from inputs

void displayEmployee(PERSON *employee);//displays the information of an employee in a readable format

void displayAllEmployees(PERSON *employees[], int numberOfEmployees);//displays all employees information readably

#endif //PERSON_H_
