#include <stdio.h>
#include <unistd.h>

int main(){
    int ret;

    printf("Teste de execução do comando ls -l\n");

    ret = execl ("/bin/ls", "ls", "-1", (char *)0);

    if(ret < 0){
        printf("Erro encontrado.\n");
    }

    return 0;
}