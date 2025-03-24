#include <unistd.h>
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 128

int findWord(char* target_file, char* word){

    int fd = open(target_file, O_RDONLY);
    if(fd < 0){
        perror("Error opening file.");
        return 0;
    }

    char buf[BUFFER_SIZE];
    int read_bytes, line_nr = 1;
    char line_buf[BUFFER_SIZE];
    int line_pos = 0;

    pid_t pid;
    int pipe_fd[2]; // read and write
    pipe(pipe_fd);
    
    while((read_bytes = read(fd, buf, BUFFER_SIZE)) > 0){
        for(int i = 0; i < read_bytes; i++){
            if(buf[i] == '\n'){ 
                // end of line, fork a child to process it
                line_buf[line_pos] = '\0';
                if((pid = fork()) == 0){
                    // Child processing
                    close(pipe_fd[0]);  
                    if(strstr(line_buf, word)){  
                        write(pipe_fd[1], &line_nr, sizeof(int));  // send line number
                    }
                    close(pipe_fd[1]);  
                    exit(0);
                }

                // reset line buffer for the next line
                line_pos = 0;
                line_nr++;  
            }else{
                line_buf[line_pos++] = buf[i];
            }
        }
    }

    // Parent processing lines given by child
    close(pipe_fd[1]);
    int status;
    while(wait(&status) > 0);  // Wait for all child processes

    // Read from pipe and print results
    int found_line = -1;
    while(read(pipe_fd[0], &found_line, sizeof(int)) > 0)
        printf("Word found at line: %d\n", found_line);
    
    if(found_line == -1)
        printf("No word has been found.\n");

    close(pipe_fd[0]);  
    close(fd);

    return 0;

}

int main(int argc, char *argv[]){

    findWord("text.txt", "crazy");
    return 0;
}