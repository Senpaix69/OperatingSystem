#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define NO_PHILOSOPHERS 5
sem_t chopsticks[NO_PHILOSOPHERS];
pthread_mutex_t mutex[NO_PHILOSOPHERS];

void *philosopher(void *id)
{
    int i = *(int *)id;
    while (1)
    {
        printf("Philosopher %d is thinking\n", i);
        if (i % 2 == 0)
        {
            sem_wait(&chopsticks[(i + 1) % NO_PHILOSOPHERS]);
            sem_wait(&chopsticks[i]);
            printf("Philosopher %d is eating\n", i);
        }
        else
        {
            sem_wait(&chopsticks[i]);
            sem_wait(&chopsticks[(i + 1) % NO_PHILOSOPHERS]);
            printf("Philosopher %d is eating\n", i);
        }

        sem_post(&chopsticks[i]);
        sem_post(&chopsticks[(i + 1) % NO_PHILOSOPHERS]);
        printf("Philosopher %d is resting\n", i);
        sleep(4);
    }
    return NULL;
}

int main()
{
    pthread_t philosophers[NO_PHILOSOPHERS];
    int ids[NO_PHILOSOPHERS];
    for (int i = 0; i < NO_PHILOSOPHERS; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
        pthread_mutex_init(&mutex[i], NULL);
    }

    for (int i = 0; i < NO_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, &philosopher, &ids[i]);
    }

    for (int i = 0; i < NO_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NO_PHILOSOPHERS; i++)
    {
        sem_destroy(&chopsticks[i]);
        pthread_mutex_destroy(&mutex[i]);
    }
    return 0;
}