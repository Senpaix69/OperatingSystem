#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 0;
    printf("Enter size: ");
    scanf("%d", &size);
    int *ptr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        printf("Enter a number: ");
        scanf("%d", &ptr[i]);
    }

    printf("Array: { ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", ptr[i]);
        if (i != size - 1)
            printf(", ");
    }
    printf(" } \n");
    free(ptr);

    return 0;
}