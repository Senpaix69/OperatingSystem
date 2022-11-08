#include <stdio.h>

int main() {
    float len = 0.f;
    float wid = 0.f;
    printf("Enter the length of rectangle: ");
    scanf("%f", &len);

    printf("Enter the width of rectangle: ");
    scanf("%f", &wid);
    
    printf("The area of rectangle: %f", len * wid);


    return 0;
}