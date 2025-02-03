#include <sys/types.h>
#include <unistd.h> /* Chamadas ao sistemas: defs e decls essenciais*/
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

int mycp(char* target_file){

    int target_fd, output_fd;
    int buff_size = 20;
    char buffer[buff_size];
    int read_bytes = 0;

    target_fd = open(target_file, O_RDONLY); // Abrir o target_file que a gente quer copiar o content
    if(target_fd == -1){
        perror("Error opening file");
        return 1;
    }

    output_fd = open("output_file_example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600); // Abrir ou criar o output_file que a gente quer colar o content do target_file
    if(output_fd == -1){
        perror("Error creating file");
        return 1;
    }

    while((read_bytes = read(target_fd, buffer, buff_size)) > 0){
        write(output_fd, buffer, read_bytes); // usar o read_bytes porque o read_bytes vai ser igual ao content do file
                                              // assim nao escrevemos lixo do buffer no file
    }

    close(target_fd);
    close(output_fd);
    return 0;
}


int main(int argc, char* argv[]){
    
    mycp(argv[1]);
    return 0;

}