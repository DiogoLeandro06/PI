#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int id;
  
    id =  getpid();
    printf("%d\n", id);
    
    fork();
    id = getpid();
    printf("%d\n", id);
    
    fork();
    id = getpid();
    printf("%d\n", id);

    return 0;
}