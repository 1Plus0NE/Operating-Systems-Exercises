#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>   

int main(int argc, char* argv[]){

    int fifo_fd = open("myfifo", O_RDONLY);
    if(fifo_fd == -1){
        perror("Error opening FIFO for reading");
        return 1;
    }
    int buffer_size = 12;
    char buf[buffer_size];
    int read_bytes;

    printf("Reading from fifo...\n");
    while((read_bytes = read(fifo_fd, buf, buffer_size)) > 0){
        write(1, buf, read_bytes); // write for stdout
    }
    close(fifo_fd);
    return 0;
}