#include <unistd.h>
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int child_to_parent(){
    pid_t pid;
    int pipe_fd[2]; // read and write
    pipe(pipe_fd);
    
    if((pid = fork()) == 0){
        // child sends sequence of integers
        close(pipe_fd[0]);
        int numbers[] = {1, 2, 3, 4, 5};
        int size = sizeof(numbers) / sizeof(numbers[0]); 
        for(int i = 0; i < size; i++){
            write(pipe_fd[1], &numbers[i], sizeof(int)); 
            printf("Value sent to parent: %d\n", numbers[i]);
            sleep(1);
        } 
        close(pipe_fd[1]);
        _exit(0);
    }
    else{
        // parent
        close(pipe_fd[1]);
        int i = -1;
        sleep(5); // add delay

        // read sequence of integers from child
        while(read(pipe_fd[0], &i, sizeof(int)) > 0)
            printf("Value received from child: %d\n", i);

        close(pipe_fd[0]);
        wait(NULL);
    }
    
    return 0;
}

// parent sends to child
int anon_pipe(){
    pid_t pid;
    int pipe_fd[2]; // read and write
    pipe(pipe_fd);
    
    if((pid = fork()) == 0){
        // child
        close(pipe_fd[1]);
        int i = -1;
        read(pipe_fd[0], &i, sizeof(int));
        printf("Value received from parent: %d\n", i);
        close(pipe_fd[0]);
    }
    else{
        // parent
        close(pipe_fd[0]);
        int i = 3;
        //sleep(3);
        write(pipe_fd[1], &i, sizeof(int));
        close(pipe_fd[1]);
        wait(NULL);
    }
    
    return 0;

}


int main(int argc, char *argv[]){

    //anon_pipe();
    child_to_parent();
    return 0;
}