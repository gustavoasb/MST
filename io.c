#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

Vertex* read_input_file(int* size, char* argv, int *totalCost){

    int nVertices = 0;
    int i = 0; //for file rows
    int j = 0; //for file columns 
    int aux = 0;
    *totalCost = 0;

    FILE* grafo;
    grafo = fopen(argv,"r");
    fscanf(grafo,"%d", &nVertices);

    Vertex* vertices = (Vertex*) malloc(sizeof(Vertex)*nVertices); //allocating the vector of vertices
    Edge* edge;

    for(i = 0; i < nVertices; i++){
        vertices[i].index = i;                  
        vertices[i].list = create_list(); //creates a list for each vertex
        for(j = 0; j < nVertices; j++){
            fscanf(grafo,"%d",&aux);
            /* 0 weight means that the vertice has no connection with the another, 
            we dont need to store it at our adjancency list*/
            if(aux != 0){                               
                edge = (Edge*) malloc(sizeof(Edge));
                edge->weight = aux;
                edge->destination = j; //storing edge information
                edge->origin = i;
                *totalCost += aux; //summing all weights, thats why we start it with 0(line 12)
                insert_list(edge,vertices[i].list); 
            }
        }
    }

    fclose(grafo);
    *size = nVertices; //making this we can have nVertices (number of vertices) in the main function
    return vertices;      
}

void _print_mst(Edge* MST, int size){
    for(int i = 0; i < size-1; i++){
        printf("%d,%d\n",MST[i].origin, MST[i].destination);
    }
}

void insertion_sort_mst(Edge* MST, int size){
    int c = 0;
    int d = 0;
    Edge aux;
    /* how the array can be very close of being already ordered, we insertion sort it */
    for(c = 1; c < size - 1 ; c++){
        d = c;
        while((d > 0 && (MST[d-1].origin > MST[d].origin)) || //sort by origin(firt number)
              (d > 0 && (MST[d-1].origin == MST[d].origin)    //sort by destination(second number)
                     && (MST[d-1].destination > MST[d].destination))){
            aux = MST[d];
            MST[d] = MST[d-1];
            MST[d-1] = aux;
            d--;
        }
    }
}

void adjust_mst(Edge* MST, int size){
    int aux;
    /*swaps the origin and the destination of an edge, for convention, to make the first number smaller the second
    A -> B = B -> A, so this do not modifies the edge information at all */
    for(int i = 0; i < size - 1; i++){ 
        if((MST[i].destination < MST[i].origin)){ 
            aux = MST[i].origin;
            MST[i].origin = MST[i].destination;
            MST[i].destination = aux;
        }
    }
}

void print_output(int mstCost, int graphCost, int unique){
    printf("MST com custo: %d\n", mstCost);
    printf("Economia vs malha totalmente conexa: %d\n", (graphCost-mstCost));
    if(unique == TRUE) printf("MST é única");
    if(unique == FALSE) printf("MST não é única");
}

void print_output_file(Edge* MST,char* argv, int size){
    FILE* output;
    output = fopen(argv,"w");
    for(int i = 0; i < size - 1 ; i++){
        fprintf(output,"%d,%d\n",MST[i].origin,MST[i].destination); 
    }
    fclose(output);
}


    