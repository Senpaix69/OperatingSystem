// grep ‘Ali’ < input.txt | wc –c > output.txt

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>

int main()
{
    int p1[2];
    if (pipe(p1) != 0)
        return 1; // error

    pid_t c1 = fork();
    if (c1 == 0)
    {
        int file = open("input.txt", O_RDONLY);

        dup2(file, STDIN_FILENO);
        close(file);

        close(p1[0]);
        dup2(p1[1], STDOUT_FILENO);
        close(p1[1]);
        execlp("grep", "grep", "Ali", NULL);
    }
    else if (c1 < 0)
        printf("Process Making Failed\n");

    pid_t c2 = fork();
    if (c2 == 0)
    {
        close(p1[1]);
        dup2(p1[0], STDIN_FILENO);
        close(p1[0]);

        int file = open("output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
        dup2(file, STDOUT_FILENO);
        close(file);
        execlp("wc", "wc", "-c", NULL);
    }
    else if (c2 < 0)
        printf("Process Making Failed\n");

    close(p1[1]);
    close(p1[0]);
    waitpid(c2, NULL, 0);

    return 0;
}