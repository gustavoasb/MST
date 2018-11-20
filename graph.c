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

int best_start(Vertex* vertices, int size){
    Node* aux;
    int smallest;
    int q;
    int start;
    for(int i = 0; i < size; i++){
        aux = vertices[i].list->head->next;
        smallest = INFINITE;
        q = 0;
        while(aux != NULL){
            if(aux->edge->weight == smallest){
                    q++;
            }
            if(aux->edge->weight < smallest){
                smallest = aux->edge->weight;
                start = aux->edge->origin;
                q = 0;
            }
            aux = aux->next;
        }
        if(q == 0){
            return start;
        }
    }
    return 0;
}

int keys_cost(int* key, int size){
    int total = 0;
    for(int i = 0; i < size; i++){ //loop summing the keys
        total += key[i];
    }
    return total;
}

void set_keys(Vertex* vertex, int size, int* key, int index, Edge* MST, int* visited, int* keyPossibilities){
    Node* aux = vertex[index].list->head->next;
    while(aux != vertex[index].list->tail->next){
        /* if the key is not setted (setted as infinite) or its smaller than a key setted before we change it, 
        and if the vertex was already visited theres no need to set a new key too */
        if((aux->edge->weight == key[aux->edge->destination]) && (visited[aux->edge->destination] == FALSE)){
            keyPossibilities[aux->edge->destination]++;
        }
        if((aux->edge->weight < key[aux->edge->destination]) && (visited[aux->edge->destination] == FALSE)){
            key[aux->edge->destination] = aux->edge->weight;
            MST[aux->edge->destination].origin = aux->edge->origin;
            keyPossibilities[aux->edge->destination] = 1;
        }
        aux = aux->next;
    }
}

int minimum_key(int* key, int size, int* visited, Edge* MST, int* unique, int* keyPossibilities){
    int smallest = INFINITE;
    int index;

    /*choose the smaller key of a unvisited vertex*/
    for(int i = 0; i < size; i++){
        if((key[i] <= smallest) && (visited[i]==FALSE)){
            smallest = key[i];
            index = i;
        }
    }
    /*if we have more than one minimum key we can have another paths, so the MST is not unique*/
    if(*unique == TRUE){ //if the MST is already proved as not unique we dont need to make that loop again
        if(keyPossibilities[index] > 1){
            *unique = FALSE;
        }
    }
    MST[index].destination = index;
    printf("%d->%d\n",MST[index].origin,MST[index].destination);
    return index;
}

int graph_mst(Vertex* vertices, int size, int* mstCost, Edge* MST){
    int alreadyVisited[size]; //boolean array to store who was visited
    int key[size]; //array that contains the path's weight for each vertex
    int keyPossibilities[size];
    int START;

    START = best_start(vertices,size);

    /*index variable will be modified to contain the MST next destination,
    the first one is the vertex that we choose to start*/
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

    for(int i = 0; i < size - 1 ; i++){
        set_keys(vertices, size, key, index, firstMST, alreadyVisited, keyPossibilities);
        index = minimum_key(key, size, alreadyVisited, firstMST, &unique, keyPossibilities);
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

    *mstCost = keys_cost(key,size); //modifies the parameter in the main function, so we can have the mst total cost
    return unique;
}

