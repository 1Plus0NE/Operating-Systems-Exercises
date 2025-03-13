#include "person.h"

Person* createPerson(char* name, int age, int id){

    Person* p = (Person*)malloc(sizeof(Person));
    if(!p){
        perror("Error allocating memory for person's struct.");
        return NULL;
    }

    p -> name = malloc(strlen(name) + 1);
    if(!p -> name){
        perror("Error allocating memory for person's name.");
        free(p);
        return NULL;
    }
    strcpy(p -> name, name);

    p -> age = age;
    p -> id = id;

    return p;

}

void updatePersonAge(Person* p, int newAge){
    p->age = newAge;
}

void freePerson(Person* p){
    if(p){
        free(p -> name);
        free(p);
    }
}