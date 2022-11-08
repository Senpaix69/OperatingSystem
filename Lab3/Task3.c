#include <stdio.h>

int main()
{
    int arr[20] = {}, num = 0, size = 0;

    for (int i = 0; i < 20; i++)
    {
        printf("Enter a number: ");
        scanf("%d", &num);
        if (num == -99)
            break;
        arr[i] = num;
        size++;
    }

    // before
    printf("Before Sorting: { ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i != size - 1)
            printf(", ");
    }
    printf(" } \n");

    // SORTING
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // after
    printf("After Sorting: { ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i != size - 1)
            printf(", ");
    }
    printf(" } \n");

    return 0;
}