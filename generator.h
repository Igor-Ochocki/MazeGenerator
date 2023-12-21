#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "maze.h"
#include <stdlib.h>

void DFS( int node, adjacency_list_t **adjacency_list, int *visited, int mazeSize );
void addAdjacencyNode(  );
void generateMaze( adjacency_list_t **adjacency_list, int mazeSize );
int isNodeInLinkedList( int node, linked_list_t *list );

#endif