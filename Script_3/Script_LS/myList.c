#include <unistd.h>
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int lsBasic(){
    execlp("ls", "ls", "-l", NULL);
    return 0;
}

int lsProcess(){

    pid_t rc_fork = fork();

    if(rc_fork == 0){
        printf("Child (pid: %d)\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        _exit(1);
    }
    else{
        int status;
        wait(&status);
        printf("Parent of %d (pid: %d)\n", rc_fork, getpid());
    }

    return 0;
}

int main(int argc, char *argv[]){
    lsBasic();
    //lsProcess();
    return 0;
}