#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int n = 10;
int buffer[10];
int in = 0, out = 0, count = 0;
void *producer(void *ptr)
{
    for (unsigned int i = 1; i < 15; i++)
    {
        while (count == n)
            ;
        buffer[in] = i;
        printf("Producer Produced: %d\n", i);
        in = (in + 1) % n;
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}
void *consumer(void *ptr)
{
    for (unsigned int i = 1; i < 15; i++)
    {
        while (count == 0)
            ;
        printf("Consumed: %d\n", buffer[out]); /*print that data*/
        out = (out + 1) % n;         /*increment counter */
        pthread_mutex_lock(&mutex);
        count--;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}
int main()
{
    pthread_t pid1, pid2;
    pthread_mutex_init(&mutex, NULL);
    /*initializing variable*/
    pthread_create(&pid2, NULL, &consumer, NULL);
    pthread_create(&pid1, NULL, &producer, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    return 0;
}