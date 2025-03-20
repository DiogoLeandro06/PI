
/*Programa utilizado para teste baseado no programa de exemplo dado no website: https://man7.org/linux/man-pages/man2/pipe.2.html*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int pipefd[2];
    char buf;
    pid_t cpid;

    if (pipe(pipefd) == -1){
        printf("Error pipe creation.\n");
        return 1;
    }
    cpid = fork();
    if (cpid == -1){
        printf("Error forking.\n");
        return 1;
    }

    if (cpid == 0) {    //child process
        if (close(pipefd[1]) == -1){
            printf("Error closing pipe.\n");
            return 1;
        }

        while (read(pipefd[0], &buf, 1) > 0) {
            if (write(STDOUT_FILENO, &buf, 1) != 1){
                printf("Error writing to stdout.\n");
                return 1;
            }
        }

        if (write(STDOUT_FILENO, "\n", 1) != 1){
            printf("Error writing to stdout.\n");
            return 1;
        }
        if (close(pipefd[0]) == -1){
            printf("Error closing pipe.\n");
            return 1;
        }

        return 0;

    } 
    else {    //parent process
        if (close(pipefd[0]) == -1) {
            printf("Error closing pipe.\n");
            return 1;
        }
        char * msg = "Testing..";
        if (write(pipefd[1], msg, strlen(msg)) != strlen(msg)){
            printf("Error writing to pipe.\n");
            return 1;
        }
        if (close(pipefd[1]) == -1){
            printf("Error closing pipe.\n");
            return 1;
        }
        if (wait(NULL) == -1){
            printf("Error waiting for child process.\n");
            return 1;
        }
        return 0;
    }
}