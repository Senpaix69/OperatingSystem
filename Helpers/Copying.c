#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    execlp("cp", "cp", "/home/senpai/Downloads/a1.c", "./", NULL);
    return 0;
}