#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define MAX_PHILOSOPHERS 3

sem_t chopsticks[N];
sem_t mutex, eating_ph;
int eating = 0;

void *philosopher(void *num)
{
    int id = *((int *)num);
    while (1)
    {
        // thinking
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // take left chopstick
        sem_wait(&chopsticks[id]);
        printf("Philosopher %d takes left chopstick %d\n", id, id);

        sem_wait(&mutex);
        if (eating >= MAX_PHILOSOPHERS)
        {
            sem_post(&chopsticks[id]);
            printf("Philosopher %d puts down left chopstick %d\n", id, id);
            sem_post(&mutex);
            continue;
        }
        eating++;
        sem_post(&mutex);

        // take right chopstick
        sem_wait(&chopsticks[(id + 1) % N]);
        printf("Philosopher %d takes right chopstick %d\n", id, (id + 1) % N);

        // eating
        sem_wait(&eating_ph);
        printf("Philosopher %d is eating\n", id);
        sleep(1);

        // put down chopsticks
        sem_post(&chopsticks[id]);
        printf("Philosopher %d puts down left chopstick %d\n", id, id);
        sem_post(&chopsticks[(id + 1) % N]);
        printf("Philosopher %d puts down right chopstick %d\n", id, (id + 1) % N);

        sem_wait(&mutex);
        eating--;
        sem_post(&mutex);
        sem_post(&eating_ph);
    }
}

int main()
{
    pthread_t philosophers[N];
    int i, num[N];
    sem_init(&mutex, 0, 1);
    sem_init(&eating_ph, 0, MAX_PHILOSOPHERS);
    for (i = 0; i < N; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
    }
    for (i = 0; i < N; i++)
    {
        num[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&num[i]);
    }
    for (i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&eating_ph);
    for (i = 0; i < N; i++)
    {
        sem_destroy(&chopsticks[i]);
    }
    return 0;
}
