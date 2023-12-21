#ifndef _MAZE_H_
#define _MAZE_H_
#define WALL_CHARACTER "\u2588"

typedef struct linked_list{
    int node;
    struct linked_list *next;
} linked_list_t;

typedef struct adjacency_list{
    int node;
    struct linked_list *adjacent;
    double weight;
} adjacency_list_t;

void printMaze( adjacency_list_t *adjacency_list, int mazeSize );
void addAdjacentNode( linked_list_t **linked_list, int node );
int getRandomAdjacentNode( linked_list_t **linked_list );
void removeAdjacentNodeAtIndex( linked_list_t **linked_list, int index);
int getRandomValue( int maxValue );

#endif
