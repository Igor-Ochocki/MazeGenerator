#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_
#include "maze.h"

/*
 * function_name:   findPathsInAdjacencyList
 * input parameters:
 *                  adjacency_list  - list of adjacency_list instances
 *                  startNode       - cell value of maze entrance
 *                  endNode         - cell value of maze exit
 *                  mazeSize        - size of generated maze provided from arguments
 * return value:    void
 * description:     This function prints all possible paths from startNode to endNode in a maze with their path weight, addidtionally
 *                  providing number of possible paths and shortest path weight
*/
void findPathsInAdjacencyList(adjacency_list_t *adjacency_list, int startNode, int endNode, int mazeSize);

/*
 * function_name:   fullDFS
 * input parameters:
 *                  node                    - cell value that the fullDFS is currently on
 *                  adjacency_list          - list of adjacency_list instances
 *                  visited                 - list of integers containing 0 and 1 representing wheter cell of index has been visited (1) or not (0)
 *                  startNode               - cell value of maze entrance
 *                  endNode                 - cell value of maze exit
 *                  mazeSize                - size of generated maze provided from arguments
 *                  pathWeigth              - weight of currently traversed path
 *                  currentPath             - linked list containing all nodes in order that led to current cell locally
 *                  shortest_path_weight    - global shortest path weight (address to an integer instance)
 *                  pathCount               - global count of found paths in a maze (address to an integer instance)
 * return value:    void
 * description:     This function finds and prints out all possible paths from startNode to endNode also counting them. Uses DFS variation
 *                  that has visited nodes only locally except globally, so that the algorithm checks all variations of steps
*/
void fullDFS(int node, adjacency_list_t *adjacency_list, int *visited, int startNode, int endNode, int mazeSize, double pathWeight, linked_list_t *currentPath, double *shortest_path_weight, int *pathCount);

/*
 * function_name:   printMazePath
 * input parameters:
 *                  adjacency_list  - list of adjacency_list instances
 *                  mazeSize        - size of generated maze provided from arguments
 *                  solutionPath    - linked list containing all cells in order that led from entranceCell to exitCell in a maze
 *                  entranceCell    - cell value that is a maze entrance
 *                  exitCell        - cell value that is an exit of a maze
 * return value:    void
 * description:     This function prints to stdout single maze with path from entranceCell to exitCell provided from solutionPath,
 *                  representing the path nodes with #
*/
void printMazePath(adjacency_list_t *adjacency_list, int mazeSize, linked_list_t *solutionPath, int entranceCell, int exitCell);

/*
 * function_name:   areNodesConnectedInPath
 * input parameters:
 *                  path            - pointer to linked list head containing all cells that are solution to a maze
 *                  first_node      - maze cell value to check if is next step in path
 *                  second_node     - maze cell value to check if is next step in path
 * return value:    int             - value of 0 or 1, where 1 represents that the first_node and second_node are concurrent in path
 * description:     This function returns value whether first_node and second_node are concurrent in path
*/
int areNodesConnectedInPath(linked_list_t *path, int first_node, int second_node);

#endif