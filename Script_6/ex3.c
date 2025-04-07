#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char * argv[]){

    int fd_stdin = open("/etc/passwd", O_RDONLY);
    int fd_stdout = open("saida.txt", O_CREAT | O_WRONLY, 0600);
    int fd_stderr = open("erros.txt", O_CREAT | O_WRONLY, 0600);
    int fd_original = dup(STDOUT_FILENO);

    dup2(fd_stdin, 0); // redirect stdin to /etc/passwd
    dup2(fd_stdout, 1); // redirect stdout to "saida.txt"
    dup2(fd_stderr, 2); // redirect stderr to "erros.txt"

    close(fd_stdout);
    close(fd_stdin);
    close(fd_stderr);

    pid_t pid = fork();

    if(pid == 0){
        // child stuff
        execlp("wc", "wc", NULL);
        _exit(0);
    }

    // parent waits
    wait(NULL);

    dup2(fd_original, STDOUT_FILENO);
    write(fd_original, "Terminei.\n", sizeof("Terminei.\n")); // writes to stdout
    close(fd_original);

    return 0;
}