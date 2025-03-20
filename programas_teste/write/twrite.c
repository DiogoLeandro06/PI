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
        printf("Error opening file %s\n",argv[1]);
        printf("%s\n",strerror(errno));
        return 0;
    }
    char * buffer = "Teste 1\n  Texto \n\nMais  Texto\n";
    int size_w = (int)strlen(buffer);
    ssize_t bytes_w = write(file_id,buffer, size_w);

    if(bytes_w < 0){
        printf("Error writing to file%s\n",argv[1]);
        printf("%s\n",strerror(errno));
    }
    else {
        printf("%zd bytes written\n",bytes_w);
    }

    int success = close(file_id);
    
    if (success != 0){
        printf("Error closing file %s\n",argv[1]);
        return 0;
    }

    return 0;
}
