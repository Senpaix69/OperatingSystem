#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <sys/sysinfo.h>

typedef struct
{
    int id;
    int *arr;
    int size;
} thread_params;

void *sort(void *arg)
{
    thread_params *params = (thread_params *)arg;
    for (int i = params->id; i < params->size; i += 2)
    {
        for (int j = params->id; j < params->size; j += 2)
        {
            if (params->arr[i] < params->arr[j])
            {
                int temp = params->arr[i];
                params->arr[i] = params->arr[j];
                params->arr[j] = temp;
            }
        }
    }
    printf("Thread: %d Sorted Array: ", params->id);
    for (int i = params->id; i < params->size; i += 2)
    {
        printf("%d, ", params->arr[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc < 2)
    {
        printf("Too Few Aruments\nUsage: ./a.out <size of array>\n");
        return -1;
    }

    int size = atoi(argv[1]);
    if (size < 0)
    {
        printf("Invalid Size\n");
        return -1;
    }

    int *ptr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        ptr[i] = rand() % 30 + 1;
    printf("Before Sorting: ");
    for (int i = 0; i < size; i++)
        printf("%d, ", ptr[i]);
    printf("\n");

    int procs = get_nprocs_conf(), cpu = 0;
    for (int i = 0; i < procs; i++)
    {
        printf("Available Processor %d\n", i);
    }

    printf("This is running on CPU: %d\n", sched_getcpu());
    printf("Enter Processor ID: ");
    scanf("%d", &cpu);

    if (cpu < 0 || cpu > procs)
    {
        printf("Error: invalid cpu\n");
        free(ptr);
        return 0;
    }

    cpu_set_t myCpu;
    CPU_ZERO(&myCpu);
    CPU_SET(cpu, &myCpu);
    sched_setaffinity(0, sizeof(cpu_set_t), &myCpu);

    printf("This is now running on CPU: %d\n", sched_getcpu());

    pthread_t th[2];
    thread_params params[2];
    for (int i = 0; i < 2; i++)
    {
        params[i] = (thread_params){
            .id = i,
            .arr = ptr,
            .size = size};
        if (pthread_create(&th[i], NULL, &sort, (void *)&params[i]) != 0)
        {
            printf("Creating Thread Failed\n");
            return -1;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Joining Thread Failed\n");
            return -1;
        }
    }

    printf("After Sorting: ");
    for (int i = 0; i < size; i++)
        printf("%d, ", ptr[i]);
    printf("\n");

    free(ptr);
    return 0;
}