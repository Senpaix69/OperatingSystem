#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *thread_function(void *arg);
int num[2] = {5, 3};

int main()
{
    // Write C code here
    pthread_t a_thread; // thread declaration
    void *result;
    pthread_create(&a_thread, NULL, thread_function, (void *)num); // thread created
    pthread_join(a_thread, &result);
    printf("inside main process \n");
    printf("thread returned:%s\n", (char *)result);
    return 0;
}

void *thread_function(void *arg)
{
    printf("inside thread\n");
    int *y = arg;
    int sum = y[0] + y[1];
    printf("sum is %d\n", sum);
    pthread_exit("sum calculated");
}