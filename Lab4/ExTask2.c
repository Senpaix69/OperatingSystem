#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Hello World\n");
    printf("I am the parent process having process id: %d\n", getpid());
    printf("Here I am before forking\n");

    pid_t id = fork();
    if(id > 0)
    {
        printf("I am a parent process with process id: %d\n", getpid());
    }
    else if(id == 0)
    {
        printf("I am a child process with process id: %d\n", getpid());
    }
    else
    {
        printf("Unable to create process\n");
    }
    
    return 0;
}