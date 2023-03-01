#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t tabaccoSem, paperSem, matchSem;
pthread_mutex_t mutex;
int numTabacco, numPaper, numMatch;

void *SmokerWithTobacco(void *arg)
{
    while (1)
    {
        sem_wait(&tabaccoSem);
        pthread_mutex_lock(&mutex);
        numPaper -= 1;
        numMatch -= 1;
        pthread_mutex_unlock(&mutex);
        printf("Smoker With Tobacco is Smoking\n\n");
    }
    return NULL;
}
void *SmokerWithPaper(void *arg)
{
    while (1)
    {
        sem_wait(&paperSem);
        pthread_mutex_lock(&mutex);
        numTabacco -= 1;
        numMatch -= 1;
        pthread_mutex_unlock(&mutex);
        printf("Smoker With Paper is Smoking\n\n");
    }
    return NULL;
}
void *SmokerWithMatch(void *arg)
{
    while (1)
    {
        sem_wait(&matchSem);
        pthread_mutex_lock(&mutex);
        numPaper -= 1;
        numTabacco -= 1;
        pthread_mutex_unlock(&mutex);
        printf("Smoker With Match is Smoking\n\n");
    }
    return NULL;
}

void *Agent(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        int num = rand() % 3 + 1;
        if (num == 1)
        {
            numPaper += 1;
            numMatch += 1;
            printf("Agent has put Paper and Match on table\n");
            sem_post(&tabaccoSem);
        }
        else if (num == 2)
        {
            numMatch += 1;
            numTabacco += 1;
            printf("Agent has put Tabacco and Match on table\n");
            sem_post(&paperSem);
        }
        else
        {
            numTabacco += 1;
            numPaper += 1;
            printf("Agent has put Paper and Tabacco on table\n");
            sem_post(&matchSem);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    sem_init(&matchSem, 0, 0);
    sem_init(&tabaccoSem, 0, 0);
    sem_init(&paperSem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t agent, sm1, sm2, sm3;

    pthread_create(&agent, NULL, &Agent, NULL);
    pthread_create(&sm1, NULL, &SmokerWithMatch, NULL);
    pthread_create(&sm2, NULL, &SmokerWithPaper, NULL);
    pthread_create(&sm3, NULL, &SmokerWithTobacco, NULL);

    pthread_join(agent, NULL);
    pthread_join(sm1, NULL);
    pthread_join(sm2, NULL);
    pthread_join(sm3, NULL);

    sem_destroy(&tabaccoSem);
    sem_destroy(&paperSem);
    sem_destroy(&matchSem);
    pthread_mutex_destroy(&mutex);
    return 0;
}