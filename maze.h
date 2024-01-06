#ifndef _MAZE_H_
#define _MAZE_H_
#define WALL_CHARACTER "\u2588"

typedef struct linked_list
{
    int node;
    struct linked_list *next;
} linked_list_t;

typedef struct adjacency_list
{
    int node;
    struct linked_list *adjacent;
    double weight;
} adjacency_list_t;

/*
 * function_name:   printMaze
 * input parameters:
 *                  adjacency_list  - pointer to adjacency list
 *                  mazeSize        - size of maze (provided from arguments)
 *                  entranceCell    - id of cell that is an entrance to the maze
 *                  exitCell        - id of cell that is an exit from the maze
 * return value:    void
 * description:     This function prints the maze structure without any additional informations about it
 */
void printMaze(adjacency_list_t *adjacency_list, int mazeSize, int entranceCell, int exitCell);

/*
 * function_name:   addAdjacentNode
 * input parameters:
 *                  linked_list     - address of a pointer to struct instance of a linked_list_t
 *                  node            - a number of a node to be added at the end of linked list
 * return value:    void
 * description:     This function adds a node to an end of a linked list. If provided linked list doesn't exist
 *                  it then creates a new instance of a linked list.
 */
void addAdjacentNode(linked_list_t **linked_list, int node);

/*
 * function_name:   getRandomAdjacentNode
 * input parameters:
 *                  linked_list     - addres of a pointer to struct instance of a linked_list_t
 * return value:    int             - random node from linked list
 * description:     This function returns random value from a linked list and then removes its occurence from it, so that
 *                  no value can be achieved twice from the same linked list without modification - it deletes the element from
 *                  instance of a linked list
 */
int getRandomAdjacentNode(linked_list_t **linked_list);

/*
 * function_name:   removeAdjacentNodeAtIndex
 * input parameters:
 *                  linked_list     - address to a pointer to struct instance of a linked_list_t
 *                  index           - index for element to be removed at
 * return value:    void
 * description:     This function removes element at index of provided linked list
 */
void removeAdjacentNodeAtIndex(linked_list_t **linked_list, int index);

/*
 * function_name:   popAdjacentNode
 * input parameters:
 *                  linked_list     - address to a pointer to struct instance of a linked_list_t
 * return value:    void
 * description:     This function removes last element from linked list
 */
void popAdjacentNode(linked_list_t **linked_list);

/*
 * function_name:   getRandomValue
 * input parameters:
 *                  maxValue        - maximum value to be returned
 * return value:    int             - random value from 0 to maxValue
 * description:     This function returns a random integer value between 0 and maxValue
 */
int getRandomValue(int maxValue);

/*
 * function_name:   printAdjacencyList
 * input parameters:
 *                  adjacency_list  - pointer to adjacency list
 *                  mazeSize        - size of maze (provided from arguments)
 * return value:    void
 * description:     This function prints to stdout structure of adjacency list and cell values
 */
void printAdjacencyList(adjacency_list_t *adjacency_list, int mazeSize);

#endif
