#include <stdio.h>
#include <stdlib.h>
#include "list.h" 
#include "graph.h"
#include "io.h"

int main(int argc, char** argv){

    int nVertices; //Number of vertices
    int mstCost; //MST total cost
    int graphCost; //Graph total cost
    int unique; //Boolean that stores if the MST is unique

    Vertex* vertices = read_input_file(&nVertices,argv[1],&graphCost);
    
    /* How graphCost returns from the read_input_file with the sum of all weights, repeateded edges are counted too.
    for example: A->B = B->A. So we need to divide it by two, this way we can have the actual cost of the graph*/
    graphCost = graphCost/2;

    /*the MST will always have Number of Vertices-1 edges, so we can make a array to store it*/
    Edge MST[nVertices-1]; 

    unique = graph_mst(vertices,nVertices, &mstCost, MST);
    adjust_mst(MST, nVertices);
    insertion_sort_mst(MST, nVertices);
    print_output(mstCost,graphCost,unique);
    print_output_file(MST,argv[2],nVertices);
    
    /* Deallocating Memory */
    for(int i = 0; i < nVertices; i++){
        free_list(vertices[i].list);
    }
    free(vertices);

    return 0;
}