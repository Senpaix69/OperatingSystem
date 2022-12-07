#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void display(int *arr, int size)
{
    printf("Array: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int smallest(int *arr, int size)
{
    int min = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (min > arr[i])
            min = arr[i];
    }
    return min;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Too few Arguments\ne.g format: ./Task.out 1 2 3 4 5 6\n");
        return 0;
    }

    if (argc == 2)
    {
        printf("The smallest number is: %s\n", argv[1]);
        return 0;
    }

    int total = argc - 1;
    int size1 = (total / 2);
    int size2 = (total - size1);

    int *arr1 = (int *)malloc(size1 * sizeof(int));
    int *arr2 = (int *)malloc(size2 * sizeof(int));

    for (int i = 0; i < size1; i++)
        arr1[i] = atoi(argv[i + 1]);
    for (int i = 0, j = size1; i < size2; i++)
        arr2[i] = atoi(argv[++j]);

    int fd1[2], fd2[2], fd3[2], fd4[2];
    if (pipe(fd1) != 0 || pipe(fd2) != 0 || pipe(fd3) != 0 || pipe(fd4) != 0)
    {
        printf("Pipe Creation Failed\n");
        return -1; // error
    }

    pid_t c1 = fork();
    if (c1 > 0) // parent
    {
        close(fd1[0]);
        write(fd1[1], arr1, size1 * sizeof(int));
        close(fd1[1]);

        pid_t c2 = fork();
        if (c2 > 0) // parent
        {
            close(fd2[0]);
            write(fd2[1], arr2, size2 * sizeof(int));
            close(fd2[1]);

            int sm1 = 0, sm2 = 0;
            close(fd3[1]);
            read(fd3[0], &sm2, sizeof(int));
            close(fd3[0]);
            close(fd4[1]);
            read(fd4[0], &sm1, sizeof(int));
            close(fd4[0]);

            if (sm1 > sm2)
                printf("The smallest number is: %d\n", sm2);
            else
                printf("The smallest number is: %d\n", sm1);
        }
        else if (c2 == 0) // child 2
        {
            int *data = (int *)malloc(size2 * sizeof(int));
            close(fd2[1]);
            read(fd2[0], data, size2 * sizeof(int));
            close(fd2[0]);

            int sm = smallest(data, size2);
            close(fd3[0]);
            write(fd3[1], &sm, sizeof(sm));
            close(fd3[1]);
        }
        else
            printf("Process Failed\n");
    }
    else if (c1 == 0) // child 1
    {
        int *data = (int *)malloc(size1 * sizeof(int));
        close(fd1[1]);
        read(fd1[0], data, size1 * sizeof(int));
        close(fd1[0]);

        int sm = smallest(data, size1);
        close(fd4[0]);
        write(fd4[1], &sm, sizeof(sm));
        close(fd4[1]);
    }
    else
        printf("Process Failed\n");

    free(arr1);
    free(arr2);
    return 0;
}