#include "personManager.h"
#define FILENAME "people.dat"

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Usage:\n");
        printf("  %s -i <name> <age>         # Insert person\n", argv[0]);
        printf("  %s -l <N>                  # List first N people\n", argv[0]);
        printf("  %s -u <name> <newAge>      # Update person by name\n", argv[0]);
        printf("  %s -o <index> <newAge>     # Update person by index\n", argv[0]);
        return 1;
    }

    Person* people[MAX_PEOPLE];
    int count = 0;

    // Carregar dados do ficheiro
    loadPeopleFromFile(FILENAME, people, &count);

    // Adicionar uma pessoa: ./program -i "André" 25
    if(strcmp(argv[1], "-i") == 0 && argc == 4){
        char* name = argv[2];
        int age = atoi(argv[3]);

        addPerson(people, &count, name, age, count + 1); // ID gerado automaticamente
        savePeopleToFile(FILENAME, people, count);
        printf("Person '%s' added successfully!\n", name);
    }
    // Listar N pessoas: ./program -l 5
    else if(strcmp(argv[1], "-l") == 0 && argc == 3){
        int n = atoi(argv[2]);
        for (int i = 0; i < n && i < count; i++) {
            printf("Person %d: %s, Age: %d, ID: %d\n", i, people[i]->name, people[i]->age, people[i]->id);
        }
    }
    // Atualizar idade pelo nome: ./program -u "André" 30
    else if(strcmp(argv[1], "-u") == 0 && argc == 4){
        char* name = argv[2];
        int newAge = atoi(argv[3]);

        for(int i = 0; i < count; i++){
            if(strcmp(people[i]->name, name) == 0){
                updatePersonAge(people[i], newAge);
                savePeopleToFile(FILENAME, people, count);
                printf("Updated %s's age to %d!\n", name, newAge);
                break;
            }
        }
    }
    // Atualizar idade pelo índice: ./program -o 2 40
    else if(strcmp(argv[1], "-o") == 0 && argc == 4){
        int index = atoi(argv[2]);
        int newAge = atoi(argv[3]);

        if(index >= 0 && index < count){
            updatePersonAge(people[index], newAge);
            savePeopleToFile(FILENAME, people, count);
            printf("Updated person at index %d to age %d!\n", index, newAge);
        }else{
            printf("Invalid index!\n");
        }
    }
    else{
        printf("Invalid command!\n");
    }

    // Libertar memória
    freeAllPeople(people, &count);
    return 0;
}