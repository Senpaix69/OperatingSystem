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

void sort(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
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
        close(p1[1]);
        read(p1[0], data, size * sizeof(int));
        close(p1[0]);

        sort(data, size);

        close(p2[0]);
        write(p2[1], data, size * sizeof(int));
        close(p2[1]);

        free(data);
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

    arr = (int *)malloc(size * sizeof(int));
    close(p2[1]);
    read(p2[0], arr, size * sizeof(int));
    close(p2[0]);

    printf("recieved from child ");
    display(arr, size);
    free(arr);

    return 0;
}