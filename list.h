#ifndef LIST
#define LIST

/* Constant Definitions */
#define TRUE 1
#define FALSE 0

/* Struct of the Edges of the graph */
typedef struct Edge{
    int weight;
    int destination;
    int origin;
}Edge;

/* Nodes of the list */
typedef struct Node{
    Edge* edge;
    struct Node* next;
}Node;

/* List struct */
typedef struct List{
    Node* head;
    Node* tail;
    int size;
}List;

/* List functions */

/* returns a brand new list */
List* create_list(); 
/* checks if the list is empty, returning true or false */
int _empty_list(List* list); 
/* inserts a edge at the end of a adjancecy list */
void insert_list(Edge* newEdge,List* list);
/* prints the entire vertex adjacency list */
void _print_list(List* list);
/* deallocate the memory of a list and its elements */
void free_list(List* list); 

#endif