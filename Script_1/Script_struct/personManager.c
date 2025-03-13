#include "personManager.h"

void addPerson(Person* people[], int* count, char* name, int age, int id){
    if(*count >= MAX_PEOPLE) {
        printf("Error: Maximum people limit reached!\n");
        return;
    }

    Person* newPerson = createPerson(name, age, id);
    if(newPerson) {
        people[*count] = newPerson;
        (*count)++;
    }
}

Person* searchPersonByID(Person* people[], int count, int id){
    for(int i = 0; i < count; i++){
        if(people[i] -> id == id){
            return people[i];
        }
    }
    return NULL;
}

void freeAllPeople(Person* people[], int* count){
    for(int i = 0; i < *count; i++){
        freePerson(people[i]);
    }
    *count = 0;
}

// Function to save all persons using system calls
void savePeopleToFile(const char* filename, Person* people[], int count){
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        perror("Error opening file for writing");
        return;
    }

    // Save number of persons
    if(write(fd, &count, sizeof(int)) != sizeof(int)){
        perror("Error writing count");
        close(fd);
        return;
    }

    // Write each person
    for(int i = 0; i < count; i++){
        int nameLength = strlen(people[i]->name) + 1;  // Include null terminator

        // Write age, ID, and name length
        if(write(fd, &(people[i]->age), sizeof(int)) != sizeof(int) ||
            write(fd, &(people[i]->id), sizeof(int)) != sizeof(int) ||
            write(fd, &nameLength, sizeof(int)) != sizeof(int) ||
            write(fd, people[i]->name, nameLength) != nameLength){
            perror("Error writing person data");
            close(fd);
            return;
        }
    }

    close(fd);
}

// Function to load persons using system calls
void loadPeopleFromFile(const char* filename, Person* people[], int* count) {
    int fd = open(filename, O_RDWR); // Abrir para leitura e escrita

    if (fd == -1) {
        perror("File does not exist. Creating a new one...");
        fd = open(filename, O_CREAT | O_RDWR, 0644);
        if (fd == -1) {
            perror("Error creating file");
            *count = 0;
            return;
        }
        *count = 0;
        close(fd);
        return;
    }

    // Verificar tamanho do ficheiro
    off_t fileSize = lseek(fd, 0, SEEK_END);
    if(fileSize == 0){
        printf("File is empty, no data loaded.\n");
        *count = 0;
        close(fd);
        return;
    }

    // Voltar ao início para ler os dados
    lseek(fd, 0, SEEK_SET);

    if(read(fd, count, sizeof(int)) != sizeof(int)){
        perror("Error reading person count");
        *count = 0;
        close(fd);
        return;
    }

    if(*count <= 0) {
        printf("Invalid count in file, resetting.\n");
        *count = 0;
        close(fd);
        return;
    }

    for (int i = 0; i < *count; i++) {
        int age, id, nameLength;

        if (read(fd, &age, sizeof(int)) != sizeof(int) ||
            read(fd, &id, sizeof(int)) != sizeof(int) ||
            read(fd, &nameLength, sizeof(int)) != sizeof(int)) {
            perror("Error reading person data");
            *count = i; // Ajustar o número real de pessoas carregadas
            break;
        }

        char* name = (char*)malloc(nameLength);
        if (!name) {
            perror("Memory allocation error");
            *count = i; // Ajustar
            break;
        }

        if (read(fd, name, nameLength) != nameLength) {
            perror("Error reading name");
            free(name);
            *count = i;
            break;
        }

        people[i] = createPerson(name, age, id);
        free(name);
    }

    close(fd);
}