#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define READERS 5
#define WRITERS 3

sem_t readers;
pthread_mutex_t mutex;

void *reader(void *arg)
{
    long no = *(int *)arg;
    printf("Reader %ld\n", no);
    pthread_exit(NULL);
}

void *writer(void *arg)
{
    long no = *(int *)arg;
    printf("Writer %ld\n", no);
    pthread_exit(NULL);
}

int main()
{
    pthread_t rdr[READERS];
    pthread_t wr[WRITERS];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&readers, 0, 5);
    for (long i = 0; i < READERS; i++)
        pthread_create(&rdr[i], NULL, &reader, (void *)i);

    for (long i = 0; i < WRITERS; i++)
        pthread_create(&wr[i], NULL, &writer, (void *)i);

    for (long i = 0; i < READERS; i++)
        pthread_join(rdr[i], NULL);

    for (long i = 0; i < WRITERS; i++)
        pthread_join(wr[i], NULL);

    sem_destroy(&readers);
    pthread_mutex_destroy(&mutex);

    return 0;
}