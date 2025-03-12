#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char ** argv){
    if (argc != 2){
        printf("Utilizar de acordo com o exemplo:\n%s <ficheiro_teste>\n",argv[0]);
        return 0;
    }

    int file_id = open(argv[1],O_WRONLY,O_CREAT);

    if (file_id == -1){
        printf("Erro ao abrir o ficheiro %s\n",argv[1]);
        printf("%s\n",strerror(errno));
        return 0;
    }
    char * buffer = "Blah\n  Blah \n\nBlah\n";
    int size_w = (int)strlen(buffer);
    ssize_t bytes_w = write(file_id,buffer, size_w);

    if(bytes_w < 0){
        printf("Erro ao ler o ficheiro\n");
        printf("%s\n",strerror(errno));
    }
    else {
        printf("Escrita de %zd bytes\n",bytes_w);
    }

    int success = close(file_id);
    
    if (success != 0){
        printf("Error closing file %s\n",argv[1]);
        //system("ereno",errno)
        return 0;
    }

    

    return 0;
}
