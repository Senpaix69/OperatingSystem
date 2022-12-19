#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// ls | grep "d" | sort | wc -l
int main()
{

    int p1[2], p2[2], p3[2];
    if (pipe(p1) != 0 || pipe(p2) != 0 || pipe(p3) != 0)
        return -1;

    pid_t c1 = fork();
    if (c1 == 0) // child
    {
        close(p1[0]);
        dup2(p1[1], STDOUT_FILENO);
        close(p1[1]);
        execlp("ls", "ls", NULL);
    }
    else if (c1 < 0) // failed
        exit(-1);

    pid_t c2 = fork();
    if (c2 == 0) // child
    {
        close(p1[1]);
        dup2(p1[0], STDIN_FILENO);
        close(p1[0]);

        close(p2[0]);
        dup2(p2[1], STDOUT_FILENO);
        close(p2[1]);

        execlp("grep", "grep", "T", NULL);
    }
    else if (c2 < 0) // failed
        exit(-1);

    pid_t c3 = fork();
    if (c3 == 0) // child
    {
        close(p1[1]);
        close(p1[0]);
        close(p2[1]);
        dup2(p2[0], STDIN_FILENO);
        close(p2[0]);

        close(p3[0]);
        dup2(p3[1], STDOUT_FILENO);
        close(p3[1]);

        execlp("sort", "sort", NULL);
    }
    else if (c3 < 0) // failed
        exit(-1);

    close(p1[1]);
    close(p1[0]);
    close(p2[1]);
    close(p2[0]);
    waitpid(c3, NULL, 0);

    return 0;
}