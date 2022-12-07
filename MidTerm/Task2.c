#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>

int main()
{
    int p1[2], p2[2], p3[2];
    if (pipe(p1) != 0 || pipe(p2) != 0 || pipe(p3) != 0)
    {
        printf("Pipes creation failed\n");
        return -1;
    }

    pid_t c1 = fork();
    if (c1 > 0) // Parent
    {
        pid_t c2 = fork();
        if (c2 > 0) // Parent
        {
            close(p1[0]);
            close(p1[1]);
            pid_t c3 = fork();
            if (c3 > 0) // Parent
            {
                close(p2[0]);
                close(p2[1]);

                pid_t c4 = fork();
                if (c4 > 0) // Parent
                {
                    close(p3[0]);
                    close(p3[1]);
                    waitpid(c4, NULL, 0);
                }
                else if (c4 == 0) // Child 4
                {
                    close(p3[1]);
                    dup2(p3[0], STDIN_FILENO);
                    close(p3[0]);

                    int file = open("output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
                    dup2(file, STDOUT_FILENO);
                    close(file);
                    execlp("wc", "wc", "-l", NULL);
                }
                else
                    printf("Forking Failed\n");
            }
            else if (c3 == 0) // Child 3
            {
                close(p2[1]);
                dup2(p2[0], STDIN_FILENO);
                close(p2[0]);

                close(p3[0]);
                dup2(p3[1], STDOUT_FILENO);
                close(p3[1]);
                execlp("sort", "sort", NULL);
            }
            else
                printf("Forking Failed\n");
        }
        else if (c2 == 0) // child 2
        {
            close(p1[1]);
            dup2(p1[0], STDIN_FILENO);
            close(p1[0]);

            close(p2[0]);
            dup2(p2[1], STDOUT_FILENO);
            close(p2[1]);

            execlp("grep", "grep", "c", NULL);
        }
        else
            printf("Forking Failed\n");
    }
    else if (c1 == 0) // child 1
    {
        close(p1[0]);
        dup2(p1[1], STDOUT_FILENO);
        close(p1[1]);
        execlp("ls", "ls", NULL);
    }
    else
        printf("Forking Failed\n");

    return 0;
}

/*
    0 -> READ (STDIN_FILENO) -> Terminal (Kernal)
    1 -> WRITE (STDOUT_FILENO) -> Terminal (Kernal)
    2 -> ERR (STDERR_FILENO) -> Terminal (Kernal)

    PIPE[2]
    4 -> READ -> 0 Ind
    5 -> WRITE -> 1 Ind

*/