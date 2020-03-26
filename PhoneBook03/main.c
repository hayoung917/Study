/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수
  --------------------------------------------------------------------------------
  first created - 2020.02.01
  writer - Hayoung Lee.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

char** names;
char** numbers;

int capacity = INIT_CAPACITY;
int n = 0;

char delim[] = " ";

void add();
void find();
void status();
void _remove();
void load();
void save();
int search(char* name);
void init_directory();
int read_line(char str[], int limit);

// 메인함수
int main(void)
{
    init_dirctory();
    process_command();

    char command[BUFFER_SIZE];

    while (1)
    {
        printf("$ ");
        scanf("%s", command);

        if (strcmp(command, "read") == 0)
            load();
        else if (strcmp(command, "add") == 0)
            add();
        else if (strcmp(command, "find") == 0)
            find();
        else if (strcmp(command, "status") == 0)
            status();
        else if (strcmp(command, "delete") == 0)
            _remove();
        else if (strcmp(command, "save") == 0)
            save();
        else if (strcmp(command, "exit") == 0)
            break;
    }

    system("pause");
    return EXIT_SUCCESS;
}

void init_directory()
{
    names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
    numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

int read_line(char str[], int limit)
{
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
    {
        if (i < limit - 1)
            str[i++] = ch;
    }
    str[i] = '\0';

    return i;
}

void load()
{
    char fileName[BUFFER_SIZE];
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    scanf("%s", fileName);

    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Open failed.\n");
        return;
    }

    while ((fscanf(fp, "%s", buf1) != EOF))
    {
        fscanf(fp, "%s", buf2);
        names[n] = strdup(buf1);
        numbers[n] = strdup(buf2);
        n++;
    }
    fclose(fp);
}

void add()
{
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];

    scanf("%s", buf1);
    scanf("%s", buf2);

    int i = n - 1;
    while (i >= 0 && strcmp(names[i], buf1) > 0)
    {
        names[i + 1] = names[i];
        numbers[i + 1] = numbers[i];
        i--;
    }
    names[i + 1] = strdup(buf1);
    numbers[i + 1] = strdup(buf2);
    n++;

    printf("%s was added successfully.\n", buf1);
}

void find()
{
    char buf[BUFFER_SIZE];
    scanf("%s", buf);

    int index = search(buf);

    if (index == -1)
    {
        printf("No person named '%s' exists.\n", buf);
    }
    else
    {
        printf("%s\n", numbers[index]);
    }
}

int search(char* name)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(name, names[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

void status()
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%s %s\n", names[i], numbers[i]);
    }
    printf("Total %d person.\n", n);
}

void _remove()
{
    char buf[BUFFER_SIZE];

    scanf("%s", buf);

    int index = search(buf);
    if (index == -1)
    {
        printf("No person named '%s' exists.\n", buf);
        return;
    }

    int j = index;
    for (; j < n - 1; j++)
    {
        names[j] = names[j + 1];
        numbers[j] = numbers[j + 1];
    }
    n--;
    printf("'%s' was deleted successfully. \n", buf);

}

void save()
{
    int i;
    char fileName[BUFFER_SIZE];
    char tmp[BUFFER_SIZE];

    scanf("%s", tmp);
    scanf("%s", fileName);

    FILE* fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("Open failed.\n");
        return;
    }
    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%s %s\n", names[i], numbers[i]);
    }
    fclose(fp);
}