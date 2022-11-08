#include <stdio.h>

int main()
{
    float a = 0.f, b = 0.f, c = 0.f;
    printf("Enter side a: ");
    scanf("%f", &a);

    printf("Enter side b: ");
    scanf("%f", &b);

    printf("Enter side c: ");
    scanf("%f", &c);

    if (a > b + c || b > a + c || c > a + b)
    {
        printf("Given Vertices do not formed a triangle \n");
    }
    else if (a != b && b != c && c != a)
    {
        printf("Given Vertices formed a Scalene triangle \n");
    }
    else if ((a == b && c != a) || (a == c && b != a) || (b == c && a != b))
    {
        printf("Given Vertices formed a Isosceles triangle \n");
    }
    else
    {
        printf("Given Vertices formed a Equilatral triangle \n");
    }

    return 0;
}