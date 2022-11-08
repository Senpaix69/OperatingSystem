#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t id;
    printf("I am the original process with PID: %d and PPID: %d\n", getpid(), getppid());

    id = fork();

    if (id == 0)
    {
        sleep(4);
        printf("I am the child process with PID: %d and PPID: %d\n", getpid(), getppid());
    }
    else if (id > 0)
    {
        printf("I am the parent process with PID: %d and PPID: %d\n", getpid(), getppid());
        printf("My child process PID is: %d\n", id);
    }
    printf("PID: %d terminates.\n", getpid());

    return 0;
}