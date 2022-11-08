#include <stdlib.h>
#include <stdio.h>

struct Employee
{
    char ID[10];
    char Name[50];
    char Gender;
    char Status[50];
    int Exp;
    int Salary;
};

int menu();
void display(struct Employee *Emp, int size);
int read(struct Employee *Emp);
void addEmployee(struct Employee *Emp, int size);
void showLowPayEmp(struct Employee *Emp, int size);
int search(struct Employee *Emp, int size, char id[]);
void save(struct Employee *Emp, int size);

int main()
{
    struct Employee *Emp = (struct Employee *)malloc(100 * sizeof(struct Employee));
    int size = read(Emp);

    while (1)
    {
        int choice = menu();
        if (choice == 1)
        {
            addEmployee(Emp, size);
            size++;
        }
        else if (choice == 2)
        {
            char id[10] = {};
            printf("Enter Employee ID: ");
            scanf("%s", id);
            int ind = search(Emp, size, id);
            if (ind != -1)
            {
                printf("%s %s %c %s %d %d \n", Emp[ind].ID, Emp[ind].Name, Emp[ind].Gender, Emp[ind].Status, Emp[ind].Exp, Emp[ind].Salary);
            }
            else
            {
                printf("No Employee Found\n");
            }
        }
        else if (choice == 3)
        {
            display(Emp, size);
        }
        else if (choice == 4)
        {
            showLowPayEmp(Emp, size);
        }
        else if (choice == 5)
        {
            save(Emp, size);
            break;
        }
        else
        {
            printf("Invalid Input\n");
        }
    }

    free(Emp);
    return 0;
}

int search(struct Employee *Emp, int size, char id[])
{
    for (int i = 0; i < size; i++)
    {
        int flag = 0;
        for (int j = 0; id[j] != '\0'; j++)
        {
            if (Emp[i].ID[j] != id[j])
                flag = 1;
        }
        if (flag == 0)
            return i;
    }
    return -1;
}

void save(struct Employee *Emp, int size)
{
    FILE *file;
    file = fopen("data.txt", "w");
    // displaying
    for (int i = 0; i < size; i++)
    {
        if (Emp[i].ID != NULL)
            fprintf(file, "%s %s %c %s %d %d", Emp[i].ID, Emp[i].Name, Emp[i].Gender, Emp[i].Status, Emp[i].Exp, Emp[i].Salary);
        if (i != size - 1)
            fputc('\n', file);
    }
    printf("File has been saved\n");
    fclose(file);
}

void showLowPayEmp(struct Employee *Emp, int size)
{
    system("clear");
    int flag = 0;
    for (int i = 0; i < size; i++)
    {
        if (Emp[i].Salary < 20000)
        {
            flag = 1;
            if (Emp[i].ID != NULL)
                printf("%s %s %c %s %d %d\n", Emp[i].ID, Emp[i].Name, Emp[i].Gender, Emp[i].Status, Emp[i].Exp, Emp[i].Salary);
        }
    }
    if (flag == 0)
        printf("No Employee who got less than 20000 pay\n");
}

void addEmployee(struct Employee *Emp, int size)
{
    system("clear");
    char id[10] = {};
    printf("Enter Employee ID: ");
    scanf("%s", id);
    if (search(Emp, size, id) == -1)
    {
        for (int i = 0; id[i] != '\0'; i++)
            Emp[size].ID[i] = id[i];
        printf("Enter Employee Name: ");
        scanf("%s", Emp[size].Name);
        printf("Enter Employee Gender: ");
        scanf(" %c", &Emp[size].Gender);
        printf("Enter Employee Status: ");
        scanf("%s", Emp[size].Status);
        printf("Enter Employee Experience: ");
        scanf("%d", &Emp[size].Exp);
        printf("Enter Employee Salary: ");
        scanf("%d", &Emp[size].Salary);
    }
    else
    {
        printf("Given ID already has been assigned to an Employee\n");
    }
}

int read(struct Employee *Emp)
{
    int size = 0;
    FILE *file;
    file = fopen("data.txt", "r");

    if (NULL == file)
    {
        printf("file can't be opened \n");
    }
    // reading
    while (!feof(file))
    {
        fscanf(file, "%s %s %c %s %d %d", Emp[size].ID, Emp[size].Name, &Emp[size].Gender, Emp[size].Status, &Emp[size].Exp, &Emp[size].Salary);
        size++;
    }
    fclose(file);
    return size;
}

void display(struct Employee *Emp, int size)
{
    system("clear");
    if (size == 0)
    {
        printf("No data found\n");
        return;
    }
    // displaying
    for (int i = 0; i < size; i++)
    {
        if (Emp[i].ID != NULL)
            printf("%s %s %c %s %d %d \n", Emp[i].ID, Emp[i].Name, Emp[i].Gender, Emp[i].Status, Emp[i].Exp, Emp[i].Salary);
    }
}

int menu()
{
    int choice = 0;
    printf("-----------------------------------------------\n");
    printf("| Enter 1: To add a record                    |\n");
    printf("| Enter 2: Search a record by ID              |\n");
    printf("| Enter 3: Show all records                   |\n");
    printf("| Enter 4: Show Employees having pay < 20000  |\n");
    printf("| Enter 5: Save and Exit                      |\n");
    printf("-----------------------------------------------\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);
    return choice;
}