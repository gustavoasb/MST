#ifndef GRAPH
#define GRAPH

/* Constant Definitions */
#define INFINITE 300000000 
#define START 0

/* Vertex Struct */
typedef struct Vertex{
    List* list;
    int index;
}Vertex;

/* Graph Functions */

/* finds graph's mst using prim's algorithm, returns if a mst is unique (true or false) */
int graph_mst(Vertex* vertices, int size, int* mstCost, Edge* MST);
/* sets the smallest paths possible to continue */
void set_keys(Vertex* vertex, int size, int* key, int index, Edge* MST, int* visited, int* keyPossibilities); 
/* finds the smaller key(path) to the next unvisited vertex and returns it index, 
that represents the vertex of the chosen path */
int minimum_key(int* key, int size, int* visited, Edge* MST, int* unique, int* keyPossibilities, List* anotherPaths);
/* return the sum of all the values of the array of keys, 
this will be equivalent to the mst total cost */
int keys_cost(int* key, int size); 
/* prints information about the vertices of the graph */
void _print_graph_info(Vertex *v, int number);


#endif