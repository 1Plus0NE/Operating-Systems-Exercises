#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
    int execs[N];  // Array to store execution counts

    for(int i = 0; i < N; i++){
        pid_t pid = fork();
        if(pid == 0){
            int count = 0;
            int res = 1; 
            while(res != 0){  
                count++;
                res = mysystem(commands[i]);  
            }
            _exit(count);  
        }
    }

    // Parent waits for all children
    for(int i = 0; i < N; i++){
        int status = 0;
        wait(&status);

        if(WIFEXITED(status)){
            int count = WEXITSTATUS(status);
            execs[i] = count;
        }
    }

    for(int i = 0; i < N; i++){
        printf("%s %d\n", commands[i], execs[i]);
    }
}


int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	return 0;
}