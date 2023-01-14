#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int fictorial(int n)
{
    if (n == 0)
        return 1;
    return n * fictorial(n - 1);
}

void *routine(void *arg)
{
    int *fict = malloc(sizeof(int));
    *fict = fictorial(*(int *)arg);
    return (void *)fict;
}

int main()
{
    int n = 0, p = 0, n_p = 0;
    printf("Enter n: ");
    scanf("%d", &n);
    do
    {
        printf("Enter p: ");
        scanf("%d", &p);
        if (n < p)
        {
            printf("p must be smaller or equals to n\n");
        }
    } while (n < p);

    n_p = n - p;

    printf("cumputing C(%d, %d)\n", n, p);

    int *nfic, *pfic, *n_pfic;
    pthread_t th[3];
    pthread_create(&th[0], NULL, &routine, &n);
    pthread_create(&th[1], NULL, &routine, &p);
    pthread_create(&th[2], NULL, &routine, &n_p);

    pthread_join(th[0], (void **)&nfic);
    pthread_join(th[1], (void **)&pfic);
    pthread_join(th[2], (void **)&n_pfic);

    int result = (*nfic / (*n_pfic * *pfic));
    printf("Result: %d\n", result);

    if (nfic)
        free(nfic);
    if (pfic)
        free(pfic);
    if (n_pfic)
        free(n_pfic);

    return 0;
}