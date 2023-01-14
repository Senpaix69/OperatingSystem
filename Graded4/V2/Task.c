#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int x, y;
} params;

void *calcSum(void *arg)
{
    int *sum = malloc(sizeof(int));
    params *th = (params *)arg;
    *sum = th->x + th->y;
    return (void *)sum;
}

int main()
{
    int *sum = NULL;
    params th_params;
    printf("Enter Num 1: ");
    scanf("%d", &th_params.x);
    printf("Enter Num 2: ");
    scanf("%d", &th_params.y);

    pthread_t t1;
    if (pthread_create(&t1, NULL, &calcSum, &th_params) != 0)
    {
        printf("Creating Thread Failed\n");
        return 1;
    }
    if (pthread_join(t1, (void **)&sum) != 0)
    {
        printf("Joining Thread Failed\n");
        return 1;
    }
    if (sum)
    {
        printf("Sum: %d\n", *sum);
        free(sum);
    }

    return 0;
}