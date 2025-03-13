#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include "person.h"
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PEOPLE 100

void addPerson(Person* people[], int* count, char* name, int age, int id);
Person* searchPersonByID(Person* people[], int count, int id);
void freeAllPeople(Person* people[], int* count);
void savePeopleToFile(const char* filename, Person* people[], int count);
void loadPeopleFromFile(const char* filename, Person* people[], int* count);

#endif