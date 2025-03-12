#include <stdio.h>
#include <unistd.h>

int main (){
    long id = (long) getpid();

    printf("Process id = %ld\n",id);

    return 0;
}