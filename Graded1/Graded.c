#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace(char *str, char *substr, char *repl, char *find);

int main(int argc, char *argv[])
{
    char *string = (char *)malloc(300 * sizeof(char));
    char *find = (char *)malloc(200 * sizeof(char));
    char *repl = (char *)malloc(200 * sizeof(char));

    if (argc > 1)
    {
        int size = strlen(argv[1]);
        for (int i = 0; i < size; i++)
        {
            string[i] = argv[1][i];
        }
    }
    else
    {
        printf("Enter C_String: ");
        scanf("%s", string);
    }

    printf("Enter SubString To Be Cut: ");
    scanf("%s", find);

    printf("Enter SubString To Be Replace: ");
    scanf("%s", repl);

    system("clear");
    printf("You entered string: ");
    printf("%s\n", string);
    printf("To Find: ");
    printf("%s\n", find);
    printf("To Replace: ");
    printf("%s\n", repl);

    char *ptr = strstr(string, find);
    if (ptr)
    {
        string = replace(string, ptr, repl, find);
        printf("Final String: %s\n", string);
    }
    else
    {
        printf("Unable to find the substring\n");
    }

    free(string);
    free(find);
    free(repl);

    return 0;
}

char *replace(char *str, char *substr, char *repl, char *find)
{
    char *newStr = (char *)malloc(300 * sizeof(char));
    int size = strlen(str) - strlen(substr);

    // saving string before substring
    for (int i = 0; i < size; i++)
    {
        newStr[i] = str[i];
    }

    // replacing sub-string
    for (int i = strlen(newStr), x = 0; repl[x] != '\0'; i++)
    {
        newStr[i] = repl[x++];
    }

    // joining rest of the string after substrings
    for (int i = strlen(newStr), x = strlen(find); substr[x] != 0; i++)
    {
        newStr[i] = substr[x++];
    }
    free(str);

    return newStr;
}