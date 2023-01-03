#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main(int argc, char **argv)
{
    printf("\nThis process is currently running on processor: %d\n", sched_getcpu());

    int nproc = get_nprocs_conf();
    printf("Available CPUs\n");
    for (int i = 0; i < nproc; i++)
        printf("Processor: %d\n", i);

    int input = -1;
    printf("Enter CPU number: ");
    while (1)
    {
        scanf("%d", &input);
        if (input > 5 || input < 0)
            printf("Invalid CPU number\nEnter CPU number again: ");
        else
            break;
    }

    cpu_set_t my_set;
    CPU_ZERO(&my_set);

    CPU_SET(input, &my_set);
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set);

    nproc = get_nprocs_conf();
    for (int i = 0; i < nproc; i++)
        printf("Processor: %d = %d \n", i, CPU_ISSET(i, &my_set));

    printf("\nThis process is currently running on processor: %d\n", sched_getcpu());
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}