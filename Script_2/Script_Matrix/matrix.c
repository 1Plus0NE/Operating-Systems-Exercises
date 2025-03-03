#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
int valueExists(int **matrix, int value) {

    // Child processing
    for(int i = 0; i < ROWS; i++){
        pid_t child = fork();
        if(child == 0){
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value) exit(1);
            }
            exit(0);
        }
    }

    // Parent processing
    for(int i = 0; i < ROWS; i++){
        int status;
        wait(&status);
        int exit_code = WEXITSTATUS(status);
        if(exit_code){
            printf("Value exists.\n");  
            return 0;
        }
    }
    printf("Value does not exist.\n"); 
    return 0;
}

int comp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// ex.6
void linesWithValue(int **matrix, int value) {

    int exit[ROWS] = { 0 }; // exit code array that contains each child's error code

    // Child processing
    for(int i = 0; i < ROWS; i++){
        pid_t child = fork();
        if(child == 0){
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value) _exit(i+1);
            }
            _exit(0);
        }
    }

    // Parent processing
    for(int i = 0; i < ROWS; i++){
        int status;
        wait(&status);
        int exit_code = WEXITSTATUS(status);
        if(exit_code > 0){
            exit[i] = WEXITSTATUS(status); // store child's error code when value is found
        }
    }

    int valid_lines[ROWS];
    int valid_count = 0;

    // Store all valid lines, ignoring all 0s
    for(int i = 0; i < ROWS; i++){
        if(exit[i] > 0){ 
            valid_lines[valid_count++] = exit[i] - 1; // adjust line value, e.g, first line is 0 in the array  
        }
    }

    // Handling if theres valid lines to be printed
    if(valid_count == 0) printf("Value not found in any row.\n");
    else{
        qsort(valid_lines, valid_count, sizeof(int), comp);
        for(int i = 0; i < valid_count; i++)
            printf("Value found at line: %d\n", valid_lines[i]);        
    }

}