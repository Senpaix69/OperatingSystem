#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define READERS 6
#define WRITERS 2

pthread_mutex_t mutex;
pthread_mutex_t room;
int max_readers = 5;

void *reader(void *arg)
{
    long id = (long)arg + 1;
    while (1)
    {
        if (pthread_mutex_trylock(&room) == 0)
        {
            if (max_readers != 0)
            {
                printf("Reader %ld has entered the room\n", id);
                max_readers--;
                printf("Reader %ld has left the room\n", id);
            }
            pthread_mutex_unlock(&room);
        }
    }
    pthread_exit(NULL);
}

void *writer(void *arg)
{
    long id = (long)arg + 1;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (pthread_mutex_trylock(&room) == 0)
        {
            if (max_readers == 0)
            {
                printf("Writer %ld has entered the room\n", id);
                max_readers = 5;
                printf("Writer %ld has left the room\n", id);
            }
            pthread_mutex_unlock(&room);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t rd[READERS];
    pthread_t wt[WRITERS];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&room, NULL);

    for (long i = 0; i < WRITERS; i++)
    {
        if (pthread_create(&wt[i], NULL, &writer, (void *)i) != 0)
        {
            printf("Error: Creating Writer Thread %ld Failed\n", i);
            return -1;
        }
    }
    for (long i = 0; i < READERS; i++)
    {
        if (pthread_create(&rd[i], NULL, &reader, (void *)i) != 0)
        {
            printf("Error: Creating Reader Thread %ld Failed\n", i);
            return -1;
        }
    }

    for (long i = 0; i < READERS; i++)
    {
        if (pthread_join(rd[i], NULL) != 0)
        {
            printf("Error: Joining Reader Thread %ld Failed\n", i);
            return -1;
        }
    }
    for (long i = 0; i < WRITERS; i++)
    {
        if (pthread_join(wt[i], NULL) != 0)
        {
            printf("Error: Joining Writer Thread %ld Failed\n", i);
            return -1;
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&room);
    pthread_exit(NULL);
}