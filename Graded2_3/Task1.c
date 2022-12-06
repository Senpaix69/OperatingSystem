#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void send(int *pip, char message[])
{
    close(pip[0]);
    write(pip[1], message, strlen(message));
    close(pip[1]);
}
void recieve(int *pip, char *message, const char *job)
{
    char rec[100] = {};
    close(pip[1]);
    read(pip[0], rec, strlen(message));
    close(pip[0]);

    printf("%s%s\n", job, rec);
}
int main()
{
    int pip1[2];
    int pip2[2];
    int pip3[2];
    int pip4[2];

    char *mes1 = "Hello";
    char *mes2 = "Hi";
    char *mes3 = "I am ill";
    char *mes4 = "All is well";
    if (pipe(pip1) == 0 && pipe(pip2) == 0 && pipe(pip3) == 0 && pipe(pip4) == 0)
    {
        pid_t c1 = fork();
        if (c1 > 0) // parent P1
        {
            send(pip1, mes1);
            wait(NULL);
            recieve(pip4, mes4, "P1 received from C3: ");
        }
        if (c1 == 0) // child C1
        {
            recieve(pip1, mes1, "C1 recieved from P1: ");
            pid_t c2 = fork();
            if (c2 > 0) // parent C1
            {
                send(pip2, mes2);
                pid_t c3 = fork();
                if (c3 > 0) // parent C1
                {
                    send(pip3, mes3);
                    wait(NULL);
                }
                else if (c3 == 0) // child C3
                {
                    recieve(pip3, mes3, "C3 recieved from C1: ");
                    send(pip4, mes4);
                    exit(0);
                }
                else
                {
                    printf("C3 making failed\n");
                    exit(-1);
                }
            }
            else if (c2 == 0)
            {
                recieve(pip2, mes2, "C2 recieved from C1: ");
                exit(0);
            }
            else
            {
                printf("C2 making failed\n");
                exit(-1);
            }
            exit(0);
        }
        else if (c1 < 0)
        {
            printf("C1 making failed\n");
            exit(-1);
        }
    }

    return 0;
}