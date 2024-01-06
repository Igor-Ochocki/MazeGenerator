#include "pathfinder.h"
#include <stdlib.h>

void findPathsInAdjacencyList(adjacency_list_t *adjacency_list, int startNode, int endNode, int mazeSize)
{
    int *visited = calloc((mazeSize * mazeSize) + 1, sizeof *visited);
    fullDFS(startNode, adjacency_list, visited, endNode, mazeSize, 0, NULL);
}
void fullDFS(int node, adjacency_list_t *adjacency_list, int *visited, int endNode, int mazeSize, int pathWeight, linked_list_t *currentPath)
{
    linked_list_t *curr = currentPath;
    pathWeight += adjacency_list[node - 1].weight;
    if (visited[node] == 1)
    {
        return;
    }
    addAdjacentNode(&currentPath, node);
    visited[node] = 1;
    if (node == endNode)
    {
        printMazePath(adjacency_list, mazeSize, currentPath);
        printf("Weight of found path : %d\n", pathWeight);
        popAdjacentNode(&currentPath);
        visited[node] = 0;
        return;
    }
    linked_list_t *adjacent = adjacency_list[node - 1].adjacent;
    while (adjacent != NULL)
    {
        if(visited[(adjacent->node)+1] != 1)
            fullDFS((adjacent->node) + 1, adjacency_list, visited, endNode, mazeSize, pathWeight, currentPath);
        adjacent = adjacent->next;
    }
    popAdjacentNode(&currentPath);
    visited[node] = 0;
}
void printMazePath(adjacency_list_t *adjacency_list, int mazeSize, linked_list_t *solutionPath)
{
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
                // Order is important
                if (isNodeInLinkedList(j + 1, adjacency_list[j].adjacent) && areNodesConnectedInPath(solutionPath, j + 2, j + 1))
                    printf("##");
                else if(isNodeInLinkedList(j + 1, adjacency_list[j].adjacent) && (areNodesConnectedInPath(solutionPath, j+1, j+1+mazeSize) || areNodesConnectedInPath(solutionPath, j+1-mazeSize, j + 1)))
                    printf("# ");
                else if (isNodeInLinkedList(j + 1, adjacency_list[j].adjacent) && !areNodesConnectedInPath(solutionPath, j + 2, j + 1))
                    printf("  ");
                else if (areNodesConnectedInPath(solutionPath, j + 1, j + 1 - mazeSize) || areNodesConnectedInPath(solutionPath, j + 1, j + 1 + mazeSize))
                    printf("#%s", WALL_CHARACTER);
                else
                    printf(" %s", WALL_CHARACTER);
            }
            else if (!areNodesConnectedInPath(solutionPath, j, j + 1) && ! areNodesConnectedInPath(solutionPath, j + 1, j + 1 - mazeSize))
                printf(" %s", WALL_CHARACTER);
            else
                printf("#%s", WALL_CHARACTER);
        }
        printf("\n");
        printf("%s", WALL_CHARACTER);
        if (i + 1 < mazeSize)
        {
            for (int j = (i + 1) * mazeSize; j < (i + 2) * mazeSize; j++)
            {
                if (isNodeInLinkedList(j - mazeSize, adjacency_list[j].adjacent) && !areNodesConnectedInPath(solutionPath, j - mazeSize + 1, j + 1))
                    printf(" ");
                else if (isNodeInLinkedList(j - mazeSize, adjacency_list[j].adjacent) && areNodesConnectedInPath(solutionPath, j - mazeSize + 1, j + 1))
                    printf("#");
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
}

int areNodesConnectedInPath(linked_list_t *path, int first_node, int second_node)
{
    linked_list_t *previous = path;
    if (path == NULL)
        return 0;
    if (path->next == NULL)
        return 0;
    path = path->next;
    while (path != NULL)
    {
        if ((previous->node == first_node && path->node == second_node) || (previous->node == second_node && path->node == first_node))
            return 1;
        previous = path;
        path = path->next;
    }
    return 0;
}