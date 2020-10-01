#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MSG_MAX 50

int n_threads = 1;

sem_t* semaphores;
char** messages;

void* Send_msg(void* rank){
    long my_rank = (long)rank;
    long dest = (my_rank+1) % n_threads;
    char* msg = new char[MSG_MAX];

    sprintf(msg, "Hello to %ld from %ld", dest, my_rank);

    messages[dest] = msg;
    sem_post(&semaphores[dest]);

    sem_wait(&semaphores[my_rank]);
    printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
    

    return NULL;

}

int main(int argc, char* argv[]){
    n_threads = atoi(argv[1]);
    pthread_t* my_threads = new pthread_t[n_threads];
    semaphores = new sem_t[n_threads];
    messages = new char*[n_threads];
    for(int i=0;i<n_threads;i++){
        messages[i] = new char[MSG_MAX];
    }
    for(long thread=0;thread<n_threads;thread++){
        pthread_create(&my_threads[thread],NULL, Send_msg, (void*)thread);
    }
    for(long i=0;i<n_threads;i++){
        pthread_join(my_threads[i], NULL);
    }
    
    delete[] semaphores;

    for(int i=0;i<n_threads;i++){
        delete[] messages[i];
    }
    delete[] messages;

}
