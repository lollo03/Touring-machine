#include <stdio.h>
#include <stdlib.h>

#define EMPTYCELL ' '

typedef struct node
{
    char val;
    struct node *next;
    struct node *prev;
} node_t;

node_t *tape = NULL;

void print_list(node_t *head)
{
    node_t *current = head;

    while (current->prev != NULL)
    {
        current = current->prev;
    }

    while (current != NULL)
    {
        printf("%c", current->val);
        current = current->next;
    }
    printf("\n");
}

node_t *next(node_t *curs)
{
    if (curs->next == NULL)
    {
        curs->next = malloc(sizeof(size_t));
        curs->next->val = EMPTYCELL;
        curs->next->prev = curs;
        curs->next->next = NULL;
    }
    return curs->next;
}

node_t *back(node_t *curs)
{
    if (curs->prev == NULL)
    {
        curs->prev = malloc(sizeof(size_t));
        curs->prev->val = EMPTYCELL;
        curs->prev->next = curs;
        curs->prev->prev = NULL;
    }
    return curs->prev;
}

char read(node_t *curs)
{
    return curs->val;
}

void write(node_t *curs, char value)
{
    curs->val = value;
}

void carica(node_t *tape, const char *arr)
{
    printf("Loading provided tape... \n");
    node_t *curs = tape;
    while (*arr != '\0')
    {
        write(curs, *arr);
        curs = next(curs);
        arr++;
    }
}

int main(int argc, char const *argv[])
{

    tape = malloc(sizeof(node_t));
    node_t *readingHead = tape;
    readingHead->val = EMPTYCELL;
    readingHead->prev = NULL;
    readingHead->next = NULL;

    if (argc == 1)
        printf("Not enough arguments! \n");

    if (argc == 3)
        carica(tape, argv[2]);

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Input file not found!\n");
        return 1;
    }

    char currentState = '\0';
    int execute = 1;

    while (!feof(fp))
    {
        char input = fgetc(fp);

        if (input == '\n' || input == ' ')
            continue;

        if (input == ':' && currentState == '\0')
        {
            execute = 1;
            currentState = fgetc(fp);
            continue;
        }

        if (input == ':' && fgetc(fp) == currentState)
        {
            execute = 1;
            continue;
        }

        if (!execute)
            continue;

        if (input == 'N' && execute)
        {
            readingHead = next(readingHead);
            continue;
        }
        if (input == 'B' && execute)
        {
            readingHead = back(readingHead);
            continue;
        }
        if (input == 'W' && execute)
        {
            write(readingHead, fgetc(fp));
            continue;
        }
        if (input == 'R' && execute)
        {
            currentState = read(readingHead);
            fp = fopen(argv[1], "r");
            execute = 0;
            continue;
        }

        if (!feof(fp))
            printf("Unknow char! %c \n", input);
    }
    print_list(tape); // < 3
    fclose(fp);
    return 0;
}
