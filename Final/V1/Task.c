#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int M, N;
int **mat1, **mat2;

int **deallocation(int **mat)
{
    for (int i = 0; i < N; i++)
    {
        free(mat[i]);
    }
    free(mat);
    return NULL;
}

void displayMat(int **arr)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%d\t", arr[i][j]);
        printf("\n");
    }
}

void *findSum(void *arg)
{
    long id = (long)arg;
    int **result = malloc(N * sizeof(int *));
    printf("Thread: %ld\n", id);
    for (int i = 0; i < N; i++)
    {
        result[i] = malloc(M * sizeof(int));
        for (int j = 0; j < M; j++)
            result[i][j] = mat1[i][j] + mat2[i][j];
    }

    printf("Resultant Matrix\n");
    displayMat(result);
    printf("\n");
    deallocation(result);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // validity arguments
    if (argc < 3)
    {
        printf("Too few argument\nFormat: ./a.out <N> <M>\n");
        return -1;
    }

    // parsing
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    if (N <= 0 || M <= 0)
    {
        printf("Error: M or N can not be negative\n");
        return -1;
    }

    mat1 = malloc(N * sizeof(int *));
    mat2 = malloc(N * sizeof(int *));

    // initializing matrixes with random values
    for (int i = 0; i < N; i++)
    {
        mat1[i] = malloc(M * sizeof(int));
        mat2[i] = malloc(M * sizeof(int));
        for (int j = 0; j < M; j++)
        {
            mat1[i][j] = rand() % 100 + 1;
            mat2[i][j] = rand() % 100 + 1;
        }
    }
    printf("Matrix A: \n");
    displayMat(mat1);
    printf("\n");
    printf("Matrix B: \n");
    displayMat(mat2);

    pthread_t threads[N];
    for (long i = 0; i < N; i++)
    {
        if (pthread_create(&threads[i], NULL, &findSum, (void *)i) != 0)
        {
            printf("Creating %ld Thread Failed\n", i);
            return -1;
        }
    }
    for (long i = 0; i < N; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("Joining %ld Thread Failed\n", i);
            return -1;
        }
    }

    mat1 = deallocation(mat1);
    mat2 = deallocation(mat2);

    return 0;
}