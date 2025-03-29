#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main (int argc, char * argv[]){

	init_vector();
	print_vector();

	unlink(SERVER);

	if(mkfifo(SERVER, 0666)){
        perror("Error creating fifo.");
        return 0;
    }

	int fd = open(SERVER, O_RDONLY);
	printf("Server open...\n");
	Msg msg;	

	while(1){
		int read_bytes = read(fd, &msg, sizeof(msg));
		while(read_bytes > 0){
			printf("Received needle %d from client %d\n", msg.needle, msg.pid);
			msg.occurrences = count_needle(msg.needle);

			// answer for client's fifo
			char fifo_name[50];
			sprintf(fifo_name, CLIENT"_%d", msg.pid);

			int fd_client = open(fifo_name, O_WRONLY);
			write(fd_client, &msg, sizeof(msg));

			close(fd_client);
		}

	}
	close(fd);
	unlink(SERVER);
	return 0;
}
