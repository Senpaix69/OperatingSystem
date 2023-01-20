#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5
#define NUM_SEATS 4

sem_t seats;
sem_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *id)
{
    int i = *((int *)id);
    while (1)
    {
        printf("Philosopher %d is thinking.\n", i);
        sem_wait(&seats);
        printf("Philosopher %d is sitting down.\n", i);
        sem_wait(&chopsticks[i]);
        sem_wait(&chopsticks[(i + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is eating.\n", i);
        sem_post(&chopsticks[i]);
        sem_post(&chopsticks[(i + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is getting up.\n", i);
        sem_post(&seats);
    }
    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    sem_init(&seats, 0, NUM_SEATS);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    sem_destroy(&seats);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
