#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (argc > 2)
        {
            FILE *fin = fopen(argv[1], "r");
            if (fin)
            {
                char readFile[2000][1000] = {};
                int lines = 0;
                while (!feof(fin))
                {
                    fgets(readFile[lines++], 1000, fin);
                    if (lines == 2000)
                    {
                        printf("Warning: Reading data exceeds the limit of 2000 lines\n");
                        break;
                    }
                }

                //           Divide And Conquror
                // ---------------------------------------
                const int eachChildGetsData = (lines / 4) == 0 ? 1 : lines / 4;
                printf("%d\n", eachChildGetsData);

                int p1[2], p2[2], p3[2], p4[2];
                if (pipe(p1) == 0 && pipe(p2) == 0 && pipe(p3) == 0 && pipe(p3) == 0 && pipe(p4) == 0)
                {
                    int c1 = fork();
                    if (c1 > 0) // parent
                    {
                        // Sending String to child 1
                        close(p1[0]);
                        for (int i = 0; i < eachChildGetsData; i++)
                            write(p1[1], readFile[i], 200);
                        close(p1[1]);

                        // if need to create more child?
                        if (lines / 4 != 0)
                        {
                            int c2 = fork();
                            if (c2 > 0) // parent
                            {
                                close(p2[0]);
                                for (int i = eachChildGetsData; i < eachChildGetsData * 2; i++)
                                    write(p2[1], readFile[i], 200);
                                close(p2[1]);

                                // Child 3
                                int c3 = fork();
                                if (c3 > 0) // parent
                                {
                                    close(p3[0]);
                                    for (int i = eachChildGetsData * 2; i < eachChildGetsData * 3; i++)
                                        write(p3[1], readFile[i], 200);
                                    close(p3[1]);

                                    int c4 = fork();
                                    if (c4 > 0) // parent
                                    {
                                        close(p4[0]);
                                        for (int i = eachChildGetsData * 3; i < eachChildGetsData * 4 || i < lines; i++)
                                            write(p4[1], readFile[i], 200);
                                        close(p4[1]);

                                        wait(NULL);
                                    }
                                    else if (c4 == 0) // C4 Child
                                    {
                                        char data[1000] = {};
                                        int row = (eachChildGetsData * 3) + 1;
                                        close(p4[1]);
                                        // printf("Child 4\n----------------------------------------\n");
                                        while (read(p4[0], data, 200))
                                        {

                                            char *ptr = strstr(data, argv[2]);
                                            if (ptr)
                                            {
                                                int col = strlen(data) - strlen(ptr) + 1;
                                                printf("Found String at: %d row and %d col\n", row, col);
                                            }
                                            row++;
                                        }
                                        close(p4[0]);
                                    }
                                    else
                                        printf("C3 Child Process Failed\n");

                                    wait(NULL);
                                }
                                else if (c3 == 0) // C3 Child
                                {
                                    char data[1000] = {};
                                    int row = (eachChildGetsData * 2) + 1;
                                    close(p3[1]);
                                    // printf("Child 3\n----------------------------------------\n");
                                    while (read(p3[0], data, 200))
                                    {

                                        char *ptr = strstr(data, argv[2]);
                                        if (ptr)
                                        {
                                            int col = strlen(data) - strlen(ptr) + 1;
                                            printf("Found String at: %d row and %d col\n", row, col);
                                        }
                                        row++;
                                    }
                                    close(p3[0]);
                                }
                                else
                                    printf("C3 Child Process Failed\n");

                                wait(NULL);
                            }
                            else if (c2 == 0) // C2 Child
                            {
                                char data[1000] = {};
                                int row = eachChildGetsData + 1;
                                close(p2[1]);
                                // printf("Child 2\n----------------------------------------\n");
                                while (read(p2[0], data, 200))
                                {

                                    char *ptr = strstr(data, argv[2]);
                                    if (ptr)
                                    {
                                        int col = strlen(data) - strlen(ptr) + 1;
                                        printf("Found String at: %d row and %d col\n", row, col);
                                    }
                                    row++;
                                }
                                close(p2[0]);
                            }
                            else
                                printf("C2 Child Process Failed\n");
                        }
                        wait(NULL);
                    }
                    else if (c1 == 0) // C1 Child
                    {
                        char data[1000] = {};
                        int row = 1;
                        close(p1[1]);
                        // printf("Child 1\n----------------------------------------\n");
                        while (read(p1[0], data, 200))
                        {

                            char *ptr = strstr(data, argv[2]);
                            if (ptr)
                            {
                                int col = strlen(data) - strlen(ptr) + 1;
                                printf("Found String at: %d row and %d col\n", row, col);
                            }
                            row++;
                        }
                        close(p1[0]);
                    }
                    else
                        printf("C1 Child Process Failed\n");
                }
                else
                    printf("Pipe Creation Failed\n");

                // ----------------------------------------

                fclose(fin);
            }
            else
                printf("Failed to read the %s file\n", argv[1]);
        }
        else
            printf("Invalid Arguments: Please Provide Filename.txt and String to search\n");
    }
    else
        printf("No arguments has been passed through command line\n");
    return 0;
}
