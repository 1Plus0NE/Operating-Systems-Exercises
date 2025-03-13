#include <sys/types.h>
#include <unistd.h> /* Chamadas ao sistemas: defs e decls essenciais*/
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

int mycat(){

    int buff_size = 128;
    char buf[buff_size];
    int read_bytes = 0;

    while((read_bytes = read(STDIN_FILENO, buf, buff_size)) > 0){ // STDIN = leitura do teclado
        // enquanto o read for maior que 0, i.e, enquanto o que está a ser lido não é EOF
        write(STDOUT_FILENO, buf, read_bytes); // STDOUT = escrita para o ecrã, i.e, output
    }

    return 0;
}

int mycat_file(char* target_file){

    int fd;
    int buff_size = 128;
    char buf[buff_size];
    int read_bytes = 0;

    fd = open(target_file, O_RDONLY); // abertura do ficheiro para leitura apenas
    if(fd < 0){
        perror("Error opening file");
        return 1;        
    }

    while((read_bytes = read(fd, buf, buff_size)) > 0){ // estou a ler do ficheiro
        write(STDOUT_FILENO, buf, read_bytes); // estou a escrever do ficheiro para o stdout
    }

    close(fd); // fechar o ficheiro que abri
    return 0;

}

int main(int argc, char* argv[]){
    
    if(argc == 2 && argv[1][0] == '1') return mycat(); // ./mycat 1
    else if(argc == 3 && argv[1][0] == '2') return mycat_file(argv[2]); // ./mycat 2 file_path
    return 0;
}