#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int show_fork(){

    pid_t rc_fork = fork();

    if(rc_fork == 0){
        printf("Child (pid: %d)\n", getpid());
        printf("Child of %d\n", getppid());
        printf("Fork value: %d\n", rc_fork);
    }
    else{
        printf("Parent of %d (pid: %d)\n", rc_fork, getpid());
    }

    return 0;

} 

int ten_processes(){

    pid_t children[10] = { 0 }; // array de filhos para que cada filho tenhamos o seu codigo de saida
    int exit[10] = { 0 }; // array de codigos de saida de cada filho

    for(int i = 0; i < 10; ++i){
        pid_t child = 0;
        if((child = fork()) == 0){ 
            // child stuff
            printf("Child (pid: %d) of parent %d\n", getpid(), getppid());
            _exit(i+1);
        }else{
            // parent stuff
            int status;
            wait(&status);
            children[i] = child; 
            if(WIFEXITED(status)) 
                exit[i] = WEXITSTATUS(status); // da store do codigo de saida do processo filho
        }
    }

    for(int i = 0; i < 10; ++i){
        printf("Exit code of child %d: %u\n", children[i], exit[i]);
    }

    return 0;

}


int ten_processes_await(){

    for(int i = 0; i < 10; ++i){
        pid_t child = 0;
        if((child = fork()) == 0){
            printf("Child (pid: %d) of parent %d\n", getpid(), getppid());
            _exit(i+1);
        }
    }
    for(int i = 0; i < 10; ++i){
        // parent stuff
        int status;
        pid_t child_wait = wait(&status);
        int exit_code = WEXITSTATUS(status);
        printf("Exit code of child %d: %u\n", child_wait, exit_code);
        
    }

}

int main(int argc, char* argv[]){

    show_fork();
    //ten_processes();
    //ten_processes_await();
    return 0;

}
