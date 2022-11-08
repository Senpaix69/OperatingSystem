#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("I am the main process with PID: %d\n\n", getpid());
    pid_t Aid = fork();
    int status = 0;
    printf("A->");
    if (Aid > 0)
    {
        wait(&status);
        printf("B");
        pid_t Bid = fork();
        if (Bid == 0)
        {
            printf("D");
            pid_t Did = fork();
            if (Did == 0)
            {
                printf("H");
                pid_t Hid = fork();
                if (Hid == 0)
                {
                    printf("I");
                }
                else if (Hid > 0)
                {
                    wait(&status);
                }
            }
            else if (Did > 0)
            {
                wait(&status);
            }
        }
        else if (Bid > 0)
        {
            wait(&status);
        }
        pid_t B1id = fork();
        if (B1id == 0)
        {
            printf("E");
        }
        else if (B1id < 0)
            wait(&status);
        pid_t B2id = fork();
        if (B2id == 0)
        {
            printf("F");
        }
        else if (B2id > 0)
            wait(&status);
    }
    else if (Aid == 0)
    {
        printf("C");
        pid_t Cid = fork();
        if (Cid == 0)
        {
            printf("G");
        }
        else if (Cid > 0)
        {
            wait(&status);
        }
    }
    else
    {
        perror("Bad Forking");
        exit(-1);
    }
    printf("\n");

    return 0;
}