#include <stdio.h>  
#include <unistd.h>
#include <pthread.h> 


pthread_mutex_t mutex;
pthread_t thread[2];
int thread_i = 1;

void * tstatus(){
    pthread_mutex_lock(&mutex);
    
    printf("Thread %d: Start\n",thread_i);
    sleep(2);
    printf("Thread %d: End\n",thread_i);
    thread_i++;

    pthread_mutex_unlock(&mutex);
}

int main(){
    
    if (pthread_mutex_init(&mutex,NULL)){
        printf("Error init mutex\n");
        return 1;    
    }

    for (int i = 0; i < 2; i++){
        if (pthread_create(&(thread[i]),NULL,&tstatus,NULL)){
            printf("Error create thread %d\n", i);
            return 1;
        }
    }
    if (pthread_join(thread[0], NULL)){
        printf("Error thread 1\n");
    }
    if (pthread_join(thread[1], NULL)){
        printf("Error thread 2\n");
    }
    

    if (pthread_mutex_destroy(&mutex)){
        printf("Error destroy mutex\n");
        return 1;    
    }
    
    return 0;
}
