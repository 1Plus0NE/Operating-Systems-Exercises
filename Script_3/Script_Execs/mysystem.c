#include "mysystem.h"


// recebe um comando por argumento
// retorna -1 se o fork falhar
// caso contrario retorna o valor do comando executado

// parse command and execute without a random number
int mysystem(const char* command){
	
    int res = -1;
    char *cmd_copy = strdup(command);
    char *args[20];  // store parsed arguments for command
    int i = 0;

    char *token = strtok(cmd_copy, " "); 
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // last argument must be NULL for execvp()

    pid_t cmd_fork = fork();
    if(cmd_fork < 0){
	free(cmd_copy);
	perror("Error upon forking");
	return -1;
    }
    if(cmd_fork == 0){
	// child do stuff
	execvp(args[0], args);
	perror("execvp failed");
	_exit(1);
    }
    else{
	// parent waits
	int status;
	waitpid(cmd_fork, &status, 0);
	if(WIFEXITED(status)) 
	    res = WEXITSTATUS(status);  // exit code of the command
	free(cmd_copy);
    }

    return res;

}

// executing aux that generates a random number between 0-3 that determines which program is going to be used
int mySystemRand(){

    int res = -1;
    pid_t first_fork = fork(); // used to exec auxiliar.c

    if(first_fork < 0){
	perror("Error upon forking");
	return -1;
    }
    if(first_fork == 0){
	// do child stuff
	printf("Child (pid: %d)\n", getpid());
	char* target[] = {"./aux", NULL}; // from auxiliar.c
	execvp(target[0], target);
	perror("Error executing aux"); // if exec fails
        _exit(1);
    }

    else{
	// parent waits
	int status;
	wait(&status);
	res = WEXITSTATUS(status);
	pid_t new_fork = fork();
	if(new_fork < 0){
	    perror("Error upon forking");
	    return -1;
	}
	if(new_fork == 0){
	    // Child stuff
	    // maybe do a switch case
	    switch(res){
		case 0:
		    printf("Executing ls -l -a -h ...\n");
		    execlp("ls", "ls", "-l", "-a", "-h", NULL);
		    break;
	
		case 1:
		    printf("Executing sleep 30 ...\n");
		    execlp("sleep", "sleep", "30", NULL);
		    break;

		case 2:
		    printf("Executing sleep 10 ...\n");
		    execlp("sleep", "sleep", "10", NULL);
		    break;

		case 3:
		    printf("Executing ps ...\n");
		    execlp("ps", "ps", NULL);
		    break;

		default:
		    printf("Doesnt match any of the options.\n");
		    _exit(1);
		    break;
	    }

	}
	else{
	    // parent waits
	    waitpid(new_fork, NULL, 0);
	}

    }

    return 0;
}
