#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int N, M;
int **mat1, **mat2;

void display(int **mat);
void deallocation(int **mat);
void *division(void *arg);

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc < 3)
    {
        printf("Too few arguments\nFormat: ./a.out <N> <M>\n");
        return -1;
    }

    // parsing
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    if (N <= 0 || M <= 0)
    {
        printf("Error: N or M can not be negative\n");
        return -1;
    }

    mat1 = malloc(N * sizeof(int *));
    mat2 = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        mat1[i] = malloc(M * sizeof(int));
        mat2[i] = malloc(M * sizeof(int));
        for (int j = 0; j < M; j++)
        {
            mat1[i][j] = rand() % 50 + 1;
            mat2[i][j] = rand() % 50 + 1;
        }
    }

    printf("Matrix A: \n");
    display(mat1);
    printf("Matrix B: \n");
    display(mat2);
    printf("\n");

    pthread_t thread[N];
    for (long i = 0; i < N; i++)
    {
        if (pthread_create(&thread[i], NULL, &division, (void *)i) != 0)
        {
            printf("Creating Thread %ld Failed Successfully", i);
            return -1;
        }
    }

    for (long i = 0; i < N; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            printf("Joining Thread %ld Failed Successfully", i);
            return -1;
        }
    }

    deallocation(mat1);
    deallocation(mat2);
    return -1;
}

void *division(void *arg)
{
    long id = (long)arg;
    int **res = malloc(N * sizeof(int *));
    printf("Thread %ld\n", id);
    for (int i = 0; i < N; i++)
    {
        res[i] = malloc(M * sizeof(int));
        for (int j = 0; j < M; j++)
        {
            res[i][j] = mat1[i][j] / mat2[i][j];
        }
    }
    printf("Resultant Matrix: \n");
    display(res);
    printf("\n");
    deallocation(res);
    return NULL;
}

void display(int **mat)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%d\t", mat[i][j]);
        printf("\n");
    }
}

void deallocation(int **mat)
{
    for (int i = 0; i < N; i++)
        free(mat[i]);
    free(mat);
}
