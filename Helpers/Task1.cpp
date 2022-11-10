#include <iostream>
using namespace std;

bool special(char ch)
{
    const char *special = "!@#$%^&*()_-';:/><{}";
    for (int i = 0; special[i] != '\0'; i++)
    {
        if (special[i] == ch)
            return true;
    }
    return false;
}

int findSecMin(int arr[], int size)
{
    int min = 0, secMin = 0;
    if (arr[0] < arr[1])
    {
        min = arr[0];
        secMin = arr[1];
    }
    else
    {
        min = arr[1];
        secMin = arr[0];
    }

    for (int i = 0; i < size; i++)
    {
        if (arr[i] < min)
        {
            secMin = min;
            min = arr[i];
        }
    }
    return secMin;
}

void checkSpecial(char arr[])
{
    int count[10] = {};
    int x = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (special(arr[i]))
        {
            count[x]++;
        }
        if (arr[i] == ' ' || arr[i + 1] == '\0')
        {
            x++;
        }
    }

    for (int i = 0; i < x; i++)
    {
        cout << count[i] << " ";
    }

    cout << "\nSecond Min: " << findSecMin(count, x) << endl;
}

int main()
{
    char arr[100] = {};
    cout << "Enter a string: ";
    cin.getline(arr, 100);

    checkSpecial(arr);

    return 0;
}