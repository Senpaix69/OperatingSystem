#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Too few arguments\n");
        return -1;
    }
    char **args = malloc((argc - 1) * sizeof(char *));
    for (int i = 0; i < (argc - 1); i++)
    {
        args[i] = argv[i + 1];
    }

    execvp(args[0], args);
}