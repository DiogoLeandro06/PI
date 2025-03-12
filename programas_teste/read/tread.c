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

    int file_id = open(argv[1],O_RDONLY);

    if (file_id == -1){
        printf("Erro ao abrir o ficheiro %s\n",argv[1]);
        printf("%s\n",strerror(errno));
        return 0;
    }

    char buffer[258];
    buffer[257] = '\0';

    ssize_t bytes_r = read(file_id,buffer, 256);

    if(bytes_r < 0){
        printf("Erro ao ler o ficheiro\n");
        printf("%s\n",strerror(errno));
    }
    else {
        printf("Leitura de %zd bytes:\n%s",bytes_r,buffer);
    }
   
    int close_s = close(file_id);
    
    if (close_s != 0){
        printf("Error closing file %s\n",argv[1]);
        //system("errno",errno)
        return 0;
    }

    return 0;
}
