#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>   

int main(int argc, char* argv[]){

    int fifo_fd = open("myfifo", O_WRONLY);
    if(fifo_fd == -1){
        perror("Error opening FIFO for writing");
        return 1;
    }
    int buffer_size = 12;
    char buf[buffer_size];
    int read_bytes;

    printf("Writing to fifo...\n");
    while((read_bytes = read(0, buf, buffer_size)) > 0){ // read from stdin
        write(fifo_fd, buf, read_bytes); 
    }
    close(fifo_fd);
    return 0;
}