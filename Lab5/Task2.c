#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd[2];
    int fdC[2];
    int x = 5;
    if (pipe(fd) == 0 && pipe(fdC) == 0)
    {
        pid_t q = fork();
        if (q > 0) // parent
        {
            close(fd[0]);
            write(fd[1], &x, sizeof(x));
            close(fd[1]);

            int mess = 0;
            close(fdC[1]);
            read(fdC[0], &mess, sizeof(mess));
            close(fdC[0]);

            printf("Parent recieved From Child: %d\n", mess);
        }
        else if (q == 0) // child
        {
            int mess = 0;
            close(fd[1]);
            read(fd[0], &mess, sizeof(mess));
            close(fd[0]);

            printf("Child recieved From Parent: %d\n", mess);

            int dx = mess * 2;
            close(fdC[0]);
            write(fdC[1], &dx, sizeof(x));
            close(fdC[1]);

            exit(0);
        }
        else
        {
            printf("Failed to created Process\n");
            exit(-1);
        }
    }
    else
    {
        printf("Pipe creation failed\n");
    }

    return 0;
}