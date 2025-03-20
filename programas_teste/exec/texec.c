#include <stdio.h>
#include <unistd.h>

int main(){
    int ret;

    printf("Testing command :\nls -l\n");

    ret = execl ("/bin/ls", "ls", "-1", (char *)0);

    if(ret < 0){
        printf("Error execl.\n");
    }

    return 0;
}