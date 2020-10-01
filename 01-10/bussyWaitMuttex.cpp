#include <iostream>
#include <stdlib.h>
#include <pthread.h>

#define n_threads 2
#define n 20

double sum = 0.0;
int flag = 0;
pthread_mutex_t mutex;

void* Thread_sumBW(void* rank) {
    long my_rank = (long)rank;
    double my_sum = 0.0;
    double factor;
    long long i;
    long long my_n = n / n_threads;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;

    if (my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = -1.0;

    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        my_sum += factor / (2 * i + 1);
    }

    while (flag != my_rank);
    sum += my_sum;
    flag = (flag + 1) % n_threads;

    return NULL;
}

void* Thread_sumMUTEX(void* rank) {
    long my_rank = (long)rank;
    double my_sum = 0.0;
    double factor;
    long long i;
    long long my_n = n / n_threads;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;

    if (my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = -1.0;

    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        my_sum += factor / (2 * i + 1);
    }

    pthread_mutex_lock(&mutex);
    sum += my_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t* thread_handles;

    thread_handles = (pthread_t*)malloc(n_threads * sizeof(pthread_t));

    pthread_mutex_init(&mutex, NULL);

    for (int thread = 0; thread < n_threads; thread++) {
        pthread_create(&thread_handles[thread], NULL, Thread_sumBW, (void*) thread);
    }

    for (int thread = 0; thread < n_threads; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }
}
