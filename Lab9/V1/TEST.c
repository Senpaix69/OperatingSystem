#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <wait.h>

int N = 250;
int numbers[1000];

void *add(void *ptr)
{
    int *sum = malloc(sizeof(int));
    int *array = (int *)ptr;
    for (int i = 0; i < N; i++)
    {
        *sum += array[i];
    }
    return (void *)sum;
}

int main()
{

    for (int i = 0; i < 1000; i++)
    {
        numbers[i] = 1;
    }

    pthread_t pid1, pid2, pid3, pid4;
    int *sum1, *sum2, *sum3, *sum4;

    pthread_create(&pid1, NULL, &add, numbers);
    pthread_create(&pid2, NULL, &add, numbers);
    pthread_create(&pid3, NULL, &add, numbers);
    pthread_create(&pid4, NULL, &add, numbers);

    pthread_join(pid1, (void **)&sum1);
    pthread_join(pid2, (void **)&sum2);
    pthread_join(pid3, (void **)&sum3);
    pthread_join(pid4, (void **)&sum4);

    int sum = *sum1 + *sum2 + *sum3 + *sum4;
    printf("sum:%d", sum);

    if (sum1)
        free(sum1);
    if (sum2)
        free(sum2);
    if (sum3)
        free(sum3);
    if (sum4)
        free(sum4);
    return 0;
}