#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    printf("\nParent process is currently running on processor: %d\n", sched_getcpu());
    if (argc < 2) // error
    {
        printf("Too few arguments\n");
        return -1;
    }

    cpu_set_t my_set;
    CPU_ZERO(&my_set);

    pid_t pid = fork();
    if (pid == 0) // child
    {
        CPU_SET(2, &my_set);
        sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
        printf("\nC1 process is currently running on processor: %d\n", sched_getcpu());

        float sum = 0.f;
        for (int i = 1; i < argc; i++)
        {
            sum += atoi(argv[i]);
        }
        printf("Average: %f\n", sum / (argc - 1));
        exit(0);
    }
    else if (pid < 0) // error
        return -1;

    pid = fork();
    if (pid == 0) // child
    {
        CPU_SET(3, &my_set);
        sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
        printf("\nC2 process is currently running on processor: %d\n", sched_getcpu());

        int min = atoi(argv[1]), max = min, val = 0;
        for (int i = 2; i < argc; i++)
        {
            val = atoi(argv[i]);
            if (max < val)
                max = val;
            if (min > val)
                min = val;
        }
        printf("Minimum: %d\nMaxmimum: %d\n", min, max);
        exit(0);
    }
    else if (pid < 0) // error
        return -1;

    pid = fork();
    if (pid == 0) // child
    {
        CPU_SET(4, &my_set);
        sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
        printf("\nC3 process is currently running on processor: %d\n", sched_getcpu());

        int *arr = (int *)malloc((argc - 1) * sizeof(int));
        for (int i = 0; i < argc - 1; i++)
            arr[i] = atoi(argv[i + 1]);

        for (int i = 0; i < argc - 1; i++)
        {
            for (int j = 0; j < argc - 1; j++)
            {
                if (arr[i] < arr[j])
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        printf("Sort List: ");
        for (int i = 0; i < argc - 1; i++)
            printf("%d ", arr[i]);
        printf("\n");

        exit(0);
    }
    else if (pid < 0) // error
        return -1;

    waitpid(pid, NULL, 0);
    return 0;
}