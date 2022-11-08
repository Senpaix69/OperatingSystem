#include <stdio.h>

void checkPrime(int num);

int main()
{
    int num = 0;
    printf("Enter a number: ");
    scanf("%d", &num);

    checkPrime(num);

    return 0;
}

void checkPrime(int num)
{
    if (num >= 0 && num <= 2)
    {
        printf("Number %d is prime\n", num);
        return;
    }

    int s = num / 2, flag = 1;

    for (int i = 2; i <= s; i++)
    {
        if (num % i == 0)
        {
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        printf("Number %d is prime\n", num);
    }
    else
    {
        printf("Number %d is not prime\n", num);
    }
}
