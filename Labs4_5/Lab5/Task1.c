#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd[2];
    if (pipe(fd) == 0)
    {
        const char *mess = "Huraira Younas";
        char message[100] = {};
        write(fd[1], mess, strlen(mess));
        read(fd[0], message, 100);

        printf("Readed From Pipe: %s\n", message);
    }
    else
    {
        printf("Pipe creation failed\n");
    }

    return 0;
}