#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int size;
int *ptr;

void *evenOdd(void *arg)
{
    long flag = (long)arg;
    printf(flag == 0 ? "Even: " : "Odd: ");
    for (int i = 0; i < size; i++)
    {
        if (flag == 0 && ptr[i] % 2 == 0)
            printf("%d ", ptr[i]);
        else if (flag == 1 && ptr[i] % 2 != 0)
            printf("%d ", ptr[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Too Few Arguments\nFormat: ./a.out <Array Elements>\n");
        return -1;
    }

    // parsing array
    size = argc - 1;
    ptr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        ptr[i] = atoi(argv[i + 1]);

    // creating threads
    pthread_t th[2];
    for (long i = 0; i < 2; i++)
    {
        if (pthread_create(&th[i], NULL, &evenOdd, (void *)i) != 0)
        {
            printf("Error Creating Threads\n");
            return -1;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Error Joining Threads\n");
            return -1;
        }
    }

    return 0;
}