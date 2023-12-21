#include <stdlib.h>
#include <stdio.h>
#include "maze.h"
#include <time.h>
#include "generator.h"
#include <math.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    int i;
    srand(time(NULL));
    adjacency_list_t *adjacency_list = malloc(sizeof *adjacency_list * n * n);
    for (i = 0; i < n * n; i++)
    {
        adjacency_list[i].node = i;
        adjacency_list[i].weight = (double)rand() / RAND_MAX * 10;
        (&adjacency_list[i])->adjacent = NULL;
    }
    generateMaze(&adjacency_list, n);
    free(adjacency_list);
    printMaze(adjacency_list, n);
}

void printMaze(adjacency_list_t *adjacency_list, int mazeSize)
{
    // for (int i = 0; i < mazeSize * mazeSize; i++)
    // {
    //     printf("%d: %g\n", adjacency_list[i].node, adjacency_list[i].weight);
    //     linked_list_t *adjacent = adjacency_list[i].adjacent;
    //     while (adjacent != NULL)
    //     {
    //         printf("%d ", adjacent->node);
    //         adjacent = adjacent->next;
    //     }
    //     printf("\n");
    // }
    usleep(10000);
    system("clear");
    for (int i = 0; i < mazeSize * 2 + 1; i++)
    {
        printf("%s", WALL_CHARACTER);
    }
    printf("\n");
    for (int i = 0; i < mazeSize; i++)
    {
        printf("%s", WALL_CHARACTER);
        for (int j = i * mazeSize; j < (i + 1) * mazeSize; j++)
        {
            if ((j + 1) % mazeSize != 0)
            {
                if (isNodeInLinkedList(j + 1, adjacency_list[j].adjacent))
                    printf("  ");
                else
                    printf(" %s", WALL_CHARACTER);
            }
            else
                printf(" %s", WALL_CHARACTER);
        }
        printf("\n");
        printf("%s", WALL_CHARACTER);
        if (i + 1 < mazeSize)
        {
            for (int j = (i + 1) * mazeSize; j < (i + 2) * mazeSize; j++)
            {
                if (isNodeInLinkedList(j - mazeSize, adjacency_list[j].adjacent))
                    printf(" ");
                else
                    printf("%s", WALL_CHARACTER);
                printf("%s", WALL_CHARACTER);
            }
        }
        else
            for (int k = 0; k < mazeSize * 2; k++)
                printf("%s", WALL_CHARACTER);
        printf("\n");
    }

    printf("\n");
}

void addAdjacentNode(linked_list_t **linked_list, int node)
{
    if (*linked_list == NULL)
    {
        *linked_list = malloc(sizeof *linked_list);
        (*linked_list)->node = node;
        (*linked_list)->next = NULL;
        return;
    }
    linked_list_t *curr = *linked_list;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    linked_list_t *new = malloc(sizeof *new);
    new->node = node;
    new->next = NULL;
    curr->next = new;
}

int getRandomValue(int maxValue)
{

    int r = rand();
    double d = (double)r / RAND_MAX;
    double val = d * (maxValue - 1);
    return round(val);
}

int getRandomAdjacentNode(linked_list_t **linked_list)
{
    if (*linked_list == NULL)
        return -1;
    int counter = 0;
    linked_list_t *start = *linked_list;
    while (start != NULL)
    {
        counter++;
        start = start->next;
    }
    int random_index = getRandomValue(counter);

    start = *linked_list;
    for (int i = 0; i < random_index; i++)
        start = start->next;
    int toReturn = (*start).node;
    removeAdjacentNodeAtIndex(linked_list, random_index);
    return toReturn;
}

void removeAdjacentNodeAtIndex(linked_list_t **linked_list, int index)
{
    if (index == 0)
    {
        *linked_list = (*linked_list)->next;
        return;
    }
    linked_list_t *first = *linked_list;
    for (int i = 0; i < index - 1; i++)
    {
        first = first->next;
    }
    linked_list_t *second = *linked_list;
    for (int i = 0; i < index + 1; i++)
    {
        second = second->next;
    }
    free(first->next);
    first->next = second;
}
