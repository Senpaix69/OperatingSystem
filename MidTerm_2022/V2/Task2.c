#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>

// sort < input.txt | grep "b" > output.txt
int main()
{
    int fd[2];
    if (pipe(fd) != 0)
    {
        printf("Pipe Creation Failed\n");
        return -1;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        int file = open("input.txt", O_RDONLY);
        dup2(file, STDIN_FILENO);
        close(file);

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("sort", "sort", "-r", NULL);
    }
    else if (pid < 0)
    {
        printf("Forking Failed\n");
        exit(-1);
    }

    pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        int file = open("output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
        dup2(file, STDOUT_FILENO);
        close(file);

        execlp("grep", "grep", "b", NULL);
    }
    else if (pid < 0)
    {
        printf("Forking Failed\n");
        exit(-1);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid, NULL, 0);

    return 0;
}