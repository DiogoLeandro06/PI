#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;

void * sum2(){
    sleep(1);
    x += 2;
}

void * printx(){
    printf("x = %d\n",x);
    sleep(2);
    printf("x = %d\n",x);
}

int main(){
    
    pthread_t t1, t2;

    if (pthread_create(&t1,NULL,&printx,NULL)){
        printf("Erro ao iniciar thread 1\n");
    }
    if (pthread_create(&t2,NULL,&sum2,NULL)){
        printf("Erro ao iniciar thread 2\n");
    }

    if (pthread_join(t1, NULL)){
        printf("Erro na thread 1\n");
    }
    if (pthread_join(t2, NULL)){
        printf("Erro na thread 2\n");
    }
    
    
    return 0;
}
