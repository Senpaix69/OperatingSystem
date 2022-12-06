#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int pip1[2];
    if (pipe(pip1) != 0)
    {
        return 1; // exit if failed creation of pipe
    }
    int file = open("out.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);

    pid_t c1 = fork();
    if (c1 > 0) // parent
    {
        pid_t c2 = fork();
        if (c2 > 0) // parent
        {
            close(pip1[0]);
            close(pip1[1]);
        }
        else if (c2 == 0) // child 2
        {
            close(pip1[1]);
            dup2(pip1[0], STDIN_FILENO);
            close(pip1[0]);

            dup2(file, STDOUT_FILENO);
            close(file);
            execlp("grep", "grep", "i", NULL);
        }
        else
        {
            printf("C2 making failed\n");
            exit(-1);
        }
        wait(NULL);
    }
    else if (c1 == 0) // child 1
    {
        close(pip1[0]);
        dup2(pip1[1], STDOUT_FILENO);
        close(pip1[1]);
        execlp("ls", "ls", "/", "-r", NULL);
    }
    else
    {
        printf("C1 making failed\n");
        exit(-1);
    }
    return 0;
}