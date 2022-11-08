#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t id;
    printf("I am the parent process and PID: %d\n", getpid());
    printf("Hello Before Forking\n");
    id = fork();
    if (id == 0)
    {
        printf("I am the child process and PID: %d\n", getpid());
        printf("I am loading , 'hello' process\n");
        execl("hello.out", "hello.out", NULL);
    }
    else if (id > 0)
    {
        wait(NULL);
        printf("I am the parent process and PID: %d\n", getpid());
    }
    else
    {
        perror("Bad Forking");
        exit(-1);
    }
    return 0;
}