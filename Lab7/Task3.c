#include <stdio.h>
int main()
{
    long int nsteps = 10000000;
    double x;
    double dx = 1.0 / nsteps;
    double pi = 0.0;
    for (long int i = 0; i < nsteps; i++)
    {
        x = (i + 0.5) * dx;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= dx;
    printf("%lf", pi);
    return 0;
}