#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5
sem_t chopsticks[NUM_PHILOSOPHERS];
pthread_mutex_t flags[NUM_PHILOSOPHERS];
int check[NUM_PHILOSOPHERS];

void *philosopher(void *id)
{
    int i = *((int *)id);
    while (1)
    {
        printf("Philosopher %d Checking For Chopstick..\n", i);

        // philosopher will check if left chopstick is available
        if (pthread_mutex_trylock(&flags[i]) == 0)
        {
            if (check[i + 1] == 0) // also check right chopstick is avaiable
            {
                sem_wait(&chopsticks[i]); // take left one
                check[i] == 1;
                printf("Philosopher %d took left chopstick..\n", i);
            }
            // if right chopstick is not available put left one down
            pthread_mutex_unlock(&flags[i]);
            check[i] = 0;
            printf("Philosopher %d put down left chopstick..\n", i);
            sem_post(&chopsticks[i]);
        }
    }
    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
        pthread_mutex_init(&flags[i], NULL);
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

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&chopsticks[i]);
        pthread_mutex_destroy(&flags[i]);
    }

    return 0;
}
