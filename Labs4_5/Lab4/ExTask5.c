#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t id = fork();

    if(id > 0)
    {
        while(1)
        {
            sleep(100);
        }
        printf("I am the parent process\n");
    }
    else if(id == 0)
    {
        printf("I am the child process\n");
        exit(0);
    }

    return 0;
}