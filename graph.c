#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

void _print_graph_info(Vertex* v, int number){
    int index = 0;
    for(index = 0; index < number; index++){
        printf("Vertex %d edges:\n", v[index].list->head->next->edge->origin);
        _print_list(v[index].list);
        printf("\n");
    }
}

int keys_cost(int* key, int size){
    int total = 0;
    for(int i = 0; i < size; i++){ 
        total += key[i];
    }
    return total;
}

void set_keys(Vertex* vertex, int size, int* key, int index, Edge* MST, int* visited, int* keyPossibilities){
    Node* aux = vertex[index].list->head->next;
    while(aux != vertex[index].list->tail->next){
        /* we can have more than one minimum key for each vertex, so we store it in the possibilities counter */
        if((aux->edge->weight == key[aux->edge->destination]) && (visited[aux->edge->destination] == FALSE)){
            keyPossibilities[aux->edge->destination]++;
        }
        /* if the key is not setted (setted as infinite) or its smaller than a key setted before we change it, 
        and if the vertex was already visited theres no need to set a new key too */
        if((aux->edge->weight < key[aux->edge->destination]) && (visited[aux->edge->destination] == FALSE)){
            key[aux->edge->destination] = aux->edge->weight;
            MST[aux->edge->destination].origin = aux->edge->origin;
            keyPossibilities[aux->edge->destination] = 1;
        }
        aux = aux->next;
    }
}

int minimum_key(int* key, int size, int* visited, Edge* MST, int* unique, int* keyPossibilities, List* anotherPaths){
    int smallest = INFINITE;
    int index;

    /* choose the smaller key of a unvisited vertex */
    for(int i = 0; i < size; i++){
        if((key[i] <= smallest) && (visited[i]==FALSE)){
            smallest = key[i];
            index = i;
        }
    }
    /* after we set the smallest one, we test if theres another minimum key 
    that could be chosen for being the next vertex, if we find it, we store it
    in the anotherPaths list */
    for(int i = 0; i < size; i++){
        if((key[i] == smallest) && (visited[i]==FALSE) && (index != i)){
            Edge* aux = (Edge*) malloc(sizeof(Edge));
            aux->destination = i;
            aux->weight = key[i];
            aux->origin = MST[i].origin;
            insert_list(aux,anotherPaths);
        }
    }
    /*if we have more than one minimum key for a vertex we can have another paths, so the MST is not unique*/
    if(*unique == TRUE){ //if the MST is already proved as not unique we dont need to make that loop again
        if(keyPossibilities[index] > 1){
            *unique = FALSE;
        }
    }
    
    MST[index].destination = index;
    return index;
}

int graph_mst(Vertex* vertices, int size, int* mstCost, Edge* MST){
    int alreadyVisited[size]; //boolean array to store who was visited
    int key[size]; //array that contains the path's with the minimum weight for each vertex
    int keyPossibilities[size]; //array that stores if there was a different path for the key setted

    /*index variable will be modified to contain the MST next destination,
    the first one is the vertex that we choose to start, defined 0 by default*/
    int index = START; 
    int unique = TRUE; //initially, we will assume that the MST is unique

    Edge firstMST[size];
    for(int i = 0; i < size; i++){
        key[i] = INFINITE;           //each key needs to be setted to infinite
        keyPossibilities[i] = 1;
        alreadyVisited[i] = FALSE;   //each vertex hasn't been visited yet
    }

    key[START] = 0; //the starter vertex key needs to be 0;
    alreadyVisited[START] = TRUE; //the starter vertex is already visited

    List* anotherPaths = create_list(); //list that stores alternative paths

    for(int i = 0; i < size - 1 ; i++){
        set_keys(vertices, size, key, index, firstMST, alreadyVisited, keyPossibilities);
        index = minimum_key(key, size, alreadyVisited, firstMST, &unique, keyPossibilities,anotherPaths);
        alreadyVisited[index] = TRUE;
    }

    /* a MST contains V-1 edges, but firstMST has V size for algorithm questions, so we have a "ghost" element,
    this element variates with the constant START (MST[START]). To solve this, has been made another loop that
    excludes this element and stores only the necessary edges, making the array easier to manipulate. */
    int j = 0; 
    for(int i = 0, j = 0; i < size ; i++){
        if(i!=START){
            MST[j] = firstMST[i];
            j++;
        }
    }

    /* if the first condition using keypossibilities fail to find if the MST is unique, we have a second test */
    /* anotherPaths stores the edges that could be chosen to be the next current vertex of the loop, if a edge
    is stored in it and is not part of the MST, we can say that the MST is not unique, so we remove from the
    it the edges that are part of the MST */
    if(unique == TRUE){
        for(int i = 0; i < size-1; i++){
            if(empty_list(anotherPaths) == TRUE){
                break;
            }
            remove_list(anotherPaths, MST[i].origin, MST[i].destination);
        }
    }

    /* if we remove all the edges, we know that all the edges stored were part of the MST. So, if the list
    is not empty, the MST is not unique, because I could through another path, resulting in
    a different mst eventually */
    if(unique == TRUE){
        if(empty_list(anotherPaths) == FALSE){
            unique = FALSE;
        }
    }

    free_list(anotherPaths);

    *mstCost = keys_cost(key,size); //modifies the parameter in the main function, so we can have the mst total cost
    return unique;
}

