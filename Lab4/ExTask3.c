#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t id;
    int status = 0;
    printf("Hello World\n");
    id = fork();

    if (id < 0)
    {
        perror("Bad Fork\n");
        exit(-1);
    }
    else if (id == 0)
    {
        printf("I am the child process\n");
    }
    else if (id > 0)
    {
        wait(&status);
        printf("I am the parent process\n");
    }

    return 0;
}