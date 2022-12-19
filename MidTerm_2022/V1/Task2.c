// ls / | grep "b" | sort -r
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2];
    if (pipe(p1) != 0 || pipe(p2) != 0)
    {
        printf("Pipes Creation Failed\n");
        return -1;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        close(p1[0]);
        dup2(p1[1], STDOUT_FILENO);
        close(p1[1]);
        execlp("ls", "ls", "/", NULL);
    }
    else if (pid < 0)
    {
        printf("Forking Failed\n");
        exit(-1);
    }

    pid = fork();
    if (pid == 0)
    {
        close(p1[1]);
        dup2(p1[0], STDIN_FILENO);
        close(p1[0]);

        close(p2[0]);
        dup2(p2[1], STDOUT_FILENO);
        close(p2[1]);
        execlp("grep", "grep", "b", NULL);
    }
    else if (pid < 0)
    {
        printf("Forking Failed\n");
        exit(-1);
    }

    pid = fork();
    if (pid == 0)
    {
        close(p1[0]);
        close(p1[1]);
        close(p2[1]);
        dup2(p2[0], STDIN_FILENO);
        close(p2[0]);
        execlp("sort", "sort", "-r", NULL);
    }
    else if (pid < 0)
    {
        printf("Forking Failed\n");
        exit(-1);
    }

    close(p1[1]);
    close(p1[2]);
    close(p2[1]);
    close(p2[2]);
    waitpid(pid, NULL, 0);
    return 0;
}