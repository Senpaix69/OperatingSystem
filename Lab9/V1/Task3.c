#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_CHARS 200
char *str;
char dataRead[200][MAX_CHARS];
int flag = 0;

struct Search_Params
{
  int id;
  int start;
  int end;
};

void *findString(void *arg)
{
  struct Search_Params *params = (struct Search_Params *)arg;
  for (int i = params->start; i < params->end && flag == 0; i++)
  {
    char *ptr = strstr(dataRead[i], str);
    if (ptr)
    {
      printf("Thread %d: %s Found at row: %d and col %ld\n", params->id, str, i + 1, strlen(dataRead[i]) - strlen(ptr));
      flag = 0;
      pthread_exit(NULL);
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s <filename> <N> <string>\n", argv[0]);
    return -1;
  }
  if (atoi(argv[2]) == 0)
  {
    fprintf(stderr, "No_Threads must be greater than 0\n");
    return -1;
  }

  FILE *fin = fopen(argv[1], "r");
  if (!fin)
  {
    printf("<%s> opening failed\n", argv[0]);
    return -1;
  }

  // parsing arguments
  str = argv[3];
  int no_threads = atoi(argv[2]);
  int lines = 0;
  while (fgets(dataRead[lines++], MAX_CHARS, fin) != 0)
  {
    if (lines == 200)
    {
      printf("Warning: Data Exceeded 200 Lines\n");
      break;
    }
  };
  fclose(fin);

  int eachThread = lines / no_threads == 0 ? 1 : lines / no_threads;
  printf("Each Thread gets: %d lines\n", eachThread);

  if (lines / no_threads == 0 && lines < 10) // just make one thread
  {
    struct Search_Params Data;
    Data.start = 0;
    Data.end = lines;
    pthread_t t1;
    pthread_create(&t1, NULL, &findString, (void *)&Data);
    pthread_join(t1, NULL);
    return 0;
  }

  pthread_t ph[no_threads];
  struct Search_Params Data[no_threads];
  for (long i = 0; i < no_threads; i++)
  {
    Data[i].id = i;
    Data[i].start = i * eachThread;
    Data[i].end = (i == (no_threads - 1) ? lines : Data[i].start + eachThread);
    if (pthread_create(&ph[i], NULL, &findString, (void *)&Data[i]) != 0)
      printf("Error Creating Thread %ld\n", i);
  }

  for (long i = 0; i < no_threads; i++)
  {
    if (pthread_join(ph[i], NULL) != 0)
      printf("Error Joining Thread %ld\n", i);
  }

  return 0;
}
