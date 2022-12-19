#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void display(int *arr, int size)
{
    printf("Array: { ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i != size - 1)
            printf(", ");
    }
    printf(" }\n");
}

void findMinMax(int *arr, int size, int *minMax)
{
    minMax[0] = arr[0];
    minMax[1] = arr[0];
    for (int i = 0; i < size; i++)
    {
        if (minMax[0] > arr[i])
            minMax[0] = arr[i];
        if (minMax[1] < arr[i])
            minMax[1] = arr[i];
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Too few arguments\nFormat e.g: ./a.out 2 4 5 6 7\n");
        return -1;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = atoi(argv[i + 1]);

    printf("Given ");
    display(arr, size);

    int p1[2], p2[2];
    if (pipe(p1) != 0 || pipe(p2) != 0)
    {
        printf("Pipes Creation Failed\n");
        return -1;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        int *data = (int *)malloc(size * sizeof(int));
        int *minMax = (int *)malloc(2 * sizeof(int));
        close(p1[1]);
        read(p1[0], data, size * sizeof(int));
        close(p1[0]);

        findMinMax(data, size, minMax);

        close(p2[0]);
        write(p2[1], minMax, 2 * sizeof(int));
        close(p2[1]);

        free(data);
        free(minMax);
        exit(0);
    }
    else if (pid < 0)
    {
        printf("Forking Failed\n");
        exit(-1);
    }

    close(p1[0]);
    write(p1[1], arr, size * sizeof(int));
    close(p1[1]);
    waitpid(pid, NULL, 0);
    free(arr);

    arr = (int *)malloc(2 * sizeof(int));
    close(p2[1]);
    read(p2[0], arr, 2 * sizeof(int));
    close(p2[0]);

    printf("recieved from child\n");
    printf("Minimum: %d\nMaximum: %d\n", arr[0], arr[1]);
    free(arr);

    return 0;
}