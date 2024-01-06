#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_
#include "maze.h"
#include "generator.h"
#include <stdio.h>

void findPathsInAdjacencyList(adjacency_list_t *adjacency_list, int startNode, int endNode, int mazeSize);
void fullDFS(int node, adjacency_list_t *adjacency_list, int *visited, int startNode, int endNode, int mazeSize, double pathWeight, linked_list_t *currentPath, double *shortest_path_weight, int *pathCount);
void printMazePath(adjacency_list_t *adjacency_list, int mazeSize, linked_list_t *solutionPath, int entranceCell, int exitCell);
int areNodesConnectedInPath(linked_list_t *path, int first_node, int second_node);

#endif