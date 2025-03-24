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

void lookupNumber(int** matrix, int value){

    int pipe_fd[2]; // read and write
    pipe(pipe_fd);

    // Child processing
    for(int i = 0; i < ROWS; i++){
        pid_t child = fork();
        if(child == 0){
            close(pipe_fd[0]);  // Close read end in child
            
            Minfo info;
            info.line_nr = i;
            info.ocur_nr = 0;
            
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value) info.ocur_nr++;
            }
            write(pipe_fd[1], &info, sizeof(Minfo));  // Send data to parent
            close(pipe_fd[1]);  // Close write end after sending
            exit(0);
        }
    }

    close(pipe_fd[1]);  // Close write end in parent

    // Parent processing
    Minfo info[ROWS];
    int index = 0;

    while(read(pipe_fd[0], &info[index], sizeof(Minfo)) > 0){
        index++;
    }
    close(pipe_fd[0]);

    // Parent waits for all childs
    for(int i = 0; i < ROWS; i++){
        wait(NULL);
    }

    // Print results
    printf("Occurrences of %d:\n", value);
    for(int i = 0; i < index; i++){
        printf("Row %d: %d times\n", info[i].line_nr, info[i].ocur_nr);
    }

}