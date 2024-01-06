#include <stdlib.h>
#include <stdio.h>
#include "maze.h"
#include <time.h>
#include "generator.h"
#include <math.h>
#include <unistd.h>
#include "pathfinder.h"

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
    int wallsSelect = getRandomValue(2);
    int randomEntranceCell = wallsSelect == 0 ? getRandomValue(n) + 1 : n * getRandomValue(n) + 1;
    int randomExitCell = wallsSelect == 0 ? getRandomValue(n) + (n * (n - 1)) + 1 : n * getRandomValue(n) + n;
    generateMaze(&adjacency_list, n);
    printMaze(adjacency_list, n, randomEntranceCell, randomExitCell);
    printAdjacencyList(adjacency_list, n);
    findPathsInAdjacencyList(adjacency_list, randomEntranceCell, randomExitCell, n);
    free(adjacency_list);
}

void printMaze(adjacency_list_t *adjacency_list, int mazeSize, int entranceCell, int exitCell)
{
    usleep(10000);
    system("clear");
    printf("Generated maze: \n");
    for (int i = 0; i < mazeSize * 2 + 1; i++)
    {
        if (entranceCell != 0 && entranceCell < mazeSize + 1 && i == entranceCell * 2 - 1)
        {
            printf(" ");
            continue;
        }
        printf("%s", WALL_CHARACTER);
    }
    printf("\n");
    for (int i = 0; i < mazeSize; i++)
    {
        if (entranceCell != 0 && entranceCell != 1 && entranceCell % mazeSize == 1 && i == entranceCell / mazeSize)
            printf(" ");
        else
            printf("%s", WALL_CHARACTER);
        char *edge = WALL_CHARACTER;
        if (exitCell != 0 && exitCell % mazeSize == 0 && i == exitCell / mazeSize - 1)
            edge = " ";
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
                printf(" %s", edge);
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
            {
                if (exitCell != 0 && exitCell != 90 && exitCell / mazeSize == mazeSize - 1 && k == (exitCell % mazeSize - 1) * 2)
                {
                    printf(" ");
                    continue;
                }
                printf("%s", WALL_CHARACTER);
            }
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

void popAdjacentNode(linked_list_t **linked_list)
{
    if (*linked_list == NULL)
        return;
    linked_list_t *current = *linked_list;
    if (current->next == NULL)
    {
        *linked_list = NULL;
        return;
    }
    int i = 0;
    while (current->next != NULL)
    {
        i++;
        current = current->next;
    }
    linked_list_t *new_last = *linked_list;
    i--;
    while (i--)
    {
        new_last = new_last->next;
    }
    free(new_last->next);
    new_last->next = NULL;
}

void printAdjacencyList(adjacency_list_t *adjacency_list, int mazeSize)
{
    printf("Maze structure (adjacency list) and cell weights\n");
    for (int i = 0; i < mazeSize * mazeSize; i++)
    {
        printf("%d (%.2f): ", adjacency_list[i].node + 1, adjacency_list[i].weight);
        linked_list_t *adjacent_nodes = adjacency_list[i].adjacent;
        while (adjacent_nodes != NULL)
        {
            printf("%d ", adjacent_nodes->node + 1);
            adjacent_nodes = adjacent_nodes->next;
        }
        printf("\n");
    }
    printf("\n");
}