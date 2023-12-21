#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "maze.h"
#include <stdlib.h>

void DFS(int node, adjacency_list_t **adjacency_list, int *visited, int mazeSize);
void removeRandomWalls(adjacency_list_t **adjacency_list, int mazeSize);
linked_list_t* getAdjacentNodes(int node, int mazeSize);
int isRemovalForbidden(int first_node, int second_node, adjacency_list_t *adjacency_list, int mazeSize);
void generateMaze(adjacency_list_t **adjacency_list, int mazeSize);
int isNodeInLinkedList(int node, linked_list_t *list);

#endif