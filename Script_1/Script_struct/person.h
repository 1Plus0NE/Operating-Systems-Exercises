#ifndef PERSON_H
#define PERSON_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct person Person;

struct person{
    char* name;
    int age;
    int id;
};

Person* createPerson(char* name, int age, int id);
void updatePersonAge(Person* p, int newAge);
void freePerson(Person* p);

#endif