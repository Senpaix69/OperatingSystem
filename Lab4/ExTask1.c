#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("I am before forking\n");
    fork();
    printf("I am after forking\n");
    printf("I am a process having process id: %d and parent process id: %d\n", getpid(), getppid());

    return 0;
}