#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *routine(void *);
int N, M;

int main(int argc, char **argv)
{
    // required arg check
    if (argc < 3)
    {
        printf("Too few arguments\nformat: ./a.out <N> <M>\n");
        printf("N: Number\nM: No_Thread\n");
        return -1;
    }

    // parsing arguments
    N = atoi(argv[1]);
    M = atoi(argv[2]);

    // validity check
    if (M < 0 || N < M)
    {
        printf("Format: N can't be less then M and M must be greater than 0\n");
        return -1;
    }

    long int fictorial = 1;
    pthread_t thread[M];

    for (long i = 0; i < M; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        if (pthread_create(&thread[i], NULL, &routine, (void *)id) != 0)
        {
            printf("Error: Creating Thread Failed\n");
            return -2;
        }
    }

    for (long i = 0; i < M; i++)
    {
        long int *res;
        if (pthread_join(thread[i], (void **)&res) != 0)
        {
            printf("Error: Joining Thread Failed\n");
            return -2;
        }
        if (res)
        {
            fictorial *= *res;
            free(res);
        }
    }
    printf("Factorial: %ld\n", fictorial);
    return 0;
}

void *routine(void *arg)
{
    int id = *(int *)arg;
    long int *fact = malloc(sizeof(long int));
    *fact = 1;
    for (int i = id; i <= N; i += M)
    {
        *fact *= i;
    }
    printf("Thread %d calculated factorial: %ld\n", id, *fact);
    free(arg);
    return (void*)fact;
}

/*  DRY RUN ROUTINE
    
    M = 2, N = 5
    -----------------------------------------------------
    Thread  Calculations            cond    Calculated
    1       1*(1+2 = 3)*(1+2+3 = 5) 5<=5    1*3*5 = 15
    2       2*(2+2 = 4)             4<=5    2*4   = 8

    Result = 15*8 = 120    
    -----------------------------------------------------

    M = 3, N = 5
    -----------------------------------------------------
    Thread  Calculations            cond    Calculated
    1       1*(1+3 = 4)             4<=5    1*4 = 4
    2       2*(2+3 = 5)             5<=5    5*2 = 10
    3       3                       3<=5    3   = 3  

    Result = 4*10*3 = 120
    -----------------------------------------------------
*/