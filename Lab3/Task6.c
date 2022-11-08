#include <stdio.h>
#include <stdlib.h>

int findSecMin(int *, int);
int main()
{

    int size = 0;
    printf("Enter the size: ");
    scanf("%d", &size);
    int *ptr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        printf("Enter a number: ");
        scanf("%d", &ptr[i]);
    }

    if (size == 1)
        printf("There is only one element\n");
    else
        printf("The sec minimum: %d\n", findSecMin(ptr, size));

    return 0;
}
int findSecMin(int *ptr, int size)
{
    int min = 0;
    int sec = 0;
    if (ptr[0] > ptr[1])
    {
        min = ptr[1];
        sec = ptr[0];
    }
    else if (ptr[0] < ptr[1])
    {
        min = ptr[0];
        sec = ptr[1];
    }

    for (int i = 2; i < size; i++)
    {
        if (ptr[i] < min)
        {
            sec = min;
            min = ptr[i];
        }
    }

    printf("Minimum %d \n", min);

    return sec;
}
