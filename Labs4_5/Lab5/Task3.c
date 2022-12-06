#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void display(int *, int);
int sum(int *, int);
int min(int *, int);

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        int *array = (int *)malloc(argc * sizeof(int));
        for (int i = 1; i < argc; i++)
        {
            array[i - 1] = atoi(argv[i]);
        }
        display(array, argc - 1);

        int fd1[2];
        int fd2[2];
        int fd3[2];
        int fd4[2];

        if (pipe(fd1) == 0 && pipe(fd2) == 0 && pipe(fd3) == 0 && pipe(fd4) == 0)
        {
            pid_t c1 = fork();
            if (c1 > 0) // parent
            {

                // sending data to child one
                close(fd1[0]);
                write(fd1[1], array, (sizeof(int) * argc - 1));
                close(fd1[1]);
                wait(NULL);

                // recieving sum from child one
                int s = 0;
                close(fd2[1]);
                read(fd2[0], &s, sizeof(s));
                close(fd2[0]);

                printf("Recieved Sum of given array from Child 1: %d\n", s);

                int c2 = fork();
                if (c2 > 0) // parent
                {
                    // sending data to child one
                    close(fd3[0]);
                    write(fd3[1], array, (sizeof(int) * argc - 1));
                    close(fd3[1]);
                    wait(NULL);

                    // recieving sum from child one
                    int minimum = 0;
                    close(fd4[1]);
                    read(fd4[0], &minimum, sizeof(minimum));
                    close(fd4[0]);

                    printf("Recieved Min of given array from Child 2: %d\n", minimum);
                }
                else if (c2 == 0) // child C2
                {
                    // receiving data from parent
                    int *getArr = (int *)malloc(argc - 1 * sizeof(int));
                    close(fd3[1]);
                    read(fd3[0], getArr, (sizeof(int) * argc - 1));
                    close(fd3[0]);

                    // sending minimum to parent
                    int minimum = min(getArr, argc - 1);
                    close(fd4[0]);
                    write(fd4[1], &minimum, sizeof(minimum));
                    close(fd4[1]);

                    free(getArr);
                    exit(0);
                }
                else
                {
                    printf("Process Creation C2 Failed\n");
                    exit(-1);
                }
            }
            else if (c1 == 0) // child C1
            {
                // receiving data from parent
                int *getArr = (int *)malloc(argc - 1 * sizeof(int));
                close(fd1[1]);
                read(fd1[0], getArr, (sizeof(int) * argc - 1));
                close(fd1[0]);

                // sending sum to parent
                int s = sum(getArr, argc - 1);
                close(fd2[0]);
                write(fd2[1], &s, sizeof(s));
                close(fd2[1]);

                free(getArr);
                exit(0);
            }
            else
            {
                printf("Process Creation C1 Failed\n");
                exit(-1);
            }
        }
        else
        {
            printf("Pipes creation failed\n");
        }

        free(array);
    }
    else
    {
        printf("Pass An Integer Array From Command Line\n");
    }

    return 0;
}

int sum(int *arr, int size)
{
    int s = 0;
    for (int i = 0; i < size; i++)
        s += arr[i];

    return s;
}

int min(int *arr, int size)
{
    int min = arr[0];
    for (int i = 0; i < size; i++)
    {
        if (min > arr[i])
            min = arr[i];
    }

    return min;
}

void display(int *arr, int size)
{
    printf("Given Array: { ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i != size - 1)
        {
            printf(", ");
        }
    }

    printf(" }\n");
}