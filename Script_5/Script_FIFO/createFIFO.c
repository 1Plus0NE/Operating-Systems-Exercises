#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    if(mkfifo("myfifo", 0666)){
        perror("Error creating fifo.");
        return 0;
    }
    return 0;
}