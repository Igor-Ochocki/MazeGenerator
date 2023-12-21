#include "generator.h"
#include <stdio.h>

void generateMaze(adjacency_list_t **adjacency_list, int mazeSize)
{
    int *visited = calloc((mazeSize * mazeSize) + 1, sizeof *visited);
    DFS(getRandomValue(mazeSize * mazeSize) + 1, adjacency_list, visited, mazeSize);
    free(visited);
    removeRandomWalls(adjacency_list, mazeSize);
}

void DFS(int current, adjacency_list_t **adjacency_list, int *visited, int mazeSize)
{
    if (visited[current] == 1)
        return;
    visited[current] = 1;
    linked_list_t *possiblyAdjacent = getAdjacentNodes(current, mazeSize);
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

linked_list_t *getAdjacentNodes(int node, int mazeSize)
{
    linked_list_t *possiblyAdjacent = NULL;
    if (node % mazeSize != 0)
        addAdjacentNode(&(possiblyAdjacent), node + 1);
    if (node % mazeSize != 1)
        addAdjacentNode(&(possiblyAdjacent), node - 1);
    if (node > mazeSize)
        addAdjacentNode(&(possiblyAdjacent), node - mazeSize);
    if (node <= mazeSize * mazeSize - mazeSize)
        addAdjacentNode(&(possiblyAdjacent), node + mazeSize);
    return possiblyAdjacent;
}

void removeRandomWalls(adjacency_list_t **adjacency_list, int mazeSize)
{
    adjacency_list_t *adjacency_list_array = *adjacency_list;
    int wallsRemoved = 0;
    int counter = 0;
    int *testedNodes;
    while (wallsRemoved < mazeSize - 2)
    {
        testedNodes = calloc((mazeSize * mazeSize), sizeof *testedNodes);
        int randomNode = getRandomValue(mazeSize * mazeSize);
        linked_list_t *adjacentNodes = getAdjacentNodes(randomNode + 1, mazeSize);
        while (adjacentNodes != NULL)
        {
            if (isRemovalForbidden(randomNode, adjacentNodes->node - 1, *adjacency_list, mazeSize) == 0 && isNodeInLinkedList(adjacentNodes->node - 1, adjacency_list_array[randomNode].adjacent) == 0)
            {
                addAdjacentNode(&(adjacency_list_array[randomNode].adjacent), adjacentNodes->node - 1);
                addAdjacentNode(&(adjacency_list_array[adjacentNodes->node - 1].adjacent), randomNode);
                wallsRemoved++;
                printMaze(*adjacency_list, mazeSize);
                if (wallsRemoved == mazeSize - 2 || counter > 50)
                    break;
            }
            counter++;
            adjacentNodes = adjacentNodes->next;
        }
        if (counter > 50)
            break;
    }
    free(testedNodes);
}

int isRemovalForbidden(int first_node, int second_node, adjacency_list_t *adjacency_list, int mazeSize)
{
    int walls_colliding = 0;
    if (abs(first_node - second_node) != 1)
    {
        if ((first_node + 1) % mazeSize != 1 && isNodeInLinkedList(first_node - 1, adjacency_list[first_node].adjacent))
            walls_colliding++;
        if ((second_node + 1) % mazeSize != 1 && isNodeInLinkedList(second_node - 1, adjacency_list[second_node].adjacent))
            walls_colliding++;
        if ((first_node + 1) % mazeSize != 1 && isNodeInLinkedList(second_node - 1, adjacency_list[first_node - 1].adjacent))
            walls_colliding++;
        if (walls_colliding == 3)
            return 1;
        walls_colliding = 0;
        if ((first_node + 1) % mazeSize != 0 && isNodeInLinkedList(first_node + 1, adjacency_list[first_node].adjacent))
            walls_colliding++;
        if ((second_node + 1) % mazeSize != 0 && isNodeInLinkedList(second_node + 1, adjacency_list[second_node].adjacent))
            walls_colliding++;
        if ((first_node + 1) % mazeSize != 0 && isNodeInLinkedList(second_node + 1, adjacency_list[first_node + 1].adjacent))
            walls_colliding++;
        if (walls_colliding == 3)
            return 1;
    }
    else
    {
        if ((first_node + 1) > mazeSize && isNodeInLinkedList(first_node - mazeSize, adjacency_list[first_node].adjacent))
            walls_colliding++;
        if ((second_node + 1) > mazeSize && isNodeInLinkedList(second_node - mazeSize, adjacency_list[second_node].adjacent))
            walls_colliding++;
        if ((first_node + 1) > mazeSize && isNodeInLinkedList(second_node - mazeSize, adjacency_list[first_node - mazeSize].adjacent))
            walls_colliding++;
        if (walls_colliding == 3)
            return 1;
        walls_colliding = 0;
        if ((first_node + 1) <= mazeSize * mazeSize - mazeSize && isNodeInLinkedList(first_node + mazeSize, adjacency_list[first_node].adjacent))
            walls_colliding++;
        if ((second_node + 1) <= mazeSize * mazeSize - mazeSize && isNodeInLinkedList(second_node + mazeSize, adjacency_list[second_node].adjacent))
            walls_colliding++;
        if ((first_node + 1) <= mazeSize * mazeSize - mazeSize && isNodeInLinkedList(second_node + mazeSize, adjacency_list[first_node + mazeSize].adjacent))
            walls_colliding++;
        if (walls_colliding == 3)
            return 1;
    }
    return 0;
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