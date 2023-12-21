#include "generator.h"
#include <stdio.h>

void generateMaze(adjacency_list_t **adjacency_list, int mazeSize)
{
    int *visited = calloc((mazeSize * mazeSize) + 1, sizeof *visited);
    DFS(getRandomValue(mazeSize * mazeSize) + 1, adjacency_list, visited, mazeSize);
}

void DFS(int current, adjacency_list_t **adjacency_list, int *visited, int mazeSize)
{
    if (visited[current] == 1)
        return;
    visited[current] = 1;
    linked_list_t *possiblyAdjacent = NULL;
    if (current % mazeSize != 0 && !visited[current + 1])
        addAdjacentNode(&(possiblyAdjacent), current + 1);
    if (current % mazeSize != 1 && !visited[current - 1])
        addAdjacentNode(&(possiblyAdjacent), current - 1);
    if (current > mazeSize && !visited[current - mazeSize])
        addAdjacentNode(&(possiblyAdjacent), current - mazeSize);
    if (current <= mazeSize * mazeSize - mazeSize && !visited[current + mazeSize])
        addAdjacentNode(&(possiblyAdjacent), current + mazeSize);
    int randomNext;
    while ((randomNext = getRandomAdjacentNode(&(possiblyAdjacent))) != -1)
    {
        adjacency_list_t *adjacency_list_array = *adjacency_list;
        if (visited[randomNext] != 1)
        {
            addAdjacentNode(&(adjacency_list_array[current - 1].adjacent), randomNext - 1);
            addAdjacentNode(&(adjacency_list_array[randomNext - 1].adjacent), current - 1);
            printMaze(*adjacency_list, mazeSize);
            DFS(randomNext, adjacency_list, visited, mazeSize);
        }
    }
}

int isNodeInLinkedList(int node, linked_list_t *list)
{
    while (list != NULL)
    {
        if (list->node == node)
            return 1;
        list = list->next;
    }
    return 0;
}