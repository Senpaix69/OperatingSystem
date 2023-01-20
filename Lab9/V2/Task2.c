#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 10

long int finalSum = 0;
pthread_mutex_t mutex;

typedef struct
{
    int *ptr;
    int id;
} params;

void *Sum(void *p)
{
    params *th = (params *)p;
    int localsum = 0;
    for (int i = 0; i < 10; i++)
        localsum += th->ptr[i];

    pthread_mutex_lock(&mutex);
    finalSum += localsum;
    pthread_mutex_unlock(&mutex);
    printf("Thread %d Calculated Local Sum: %d\n", th->id, localsum);
    return NULL;
}

int main()
{
    srand(time(NULL));
    int array[10] = {};
    printf("Array: ");
    for (int i = 0; i < 10; i++)
    {
        array[i] = rand() % 20 + 1;
        printf("%d ", array[i]);
    }
    printf("\n");

    pthread_t th[MAX_THREADS];
    params th_params[MAX_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < MAX_THREADS; i++)
    {
        th_params[i].id = i;
        th_params[i].ptr = array;
        if (pthread_create(&th[i], NULL, &Sum, (void *) &th_params[i]) != 0)
        {
            printf("Error: Creating Thread Failed\n");
            return -1;
        }
    }

    for (long i = 0; i < MAX_THREADS; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Error: Joining Thread Failed\n");
            return -1;
        }
    }

    printf("Final Sum: %ld\n", finalSum);
    return 0;
}