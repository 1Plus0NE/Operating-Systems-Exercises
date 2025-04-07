#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[]){

    int pipe_fd[2]; // read and write
    if(pipe(pipe_fd) == -1){
        perror("initializing pipe.");
        exit(1);
    }
    
    pid_t pid = fork();
    if(pid == 0){
        // child stuff
        close(pipe_fd[1]); // close write
        dup2(pipe_fd[0], STDIN_FILENO); // redirect stdin to pipe_fd[0] (read)
        close(pipe_fd[0]); // close read

        execlp("wc", "wc", NULL); // wc reads from redirected stdin (pipe_fd[0] => read)
        _exit(1);
    }

    // parent stuff
    close(pipe_fd[0]); // close read
    int read_bytes = 0;
    int buf_size = 32;
    char buffer[buf_size];

    while((read_bytes = read(STDIN_FILENO, buffer, buf_size)) > 0)
        write(pipe_fd[1], buffer, read_bytes); // write

    close(pipe_fd[1]); // close write
    wait(NULL);
    
    return 0;
}