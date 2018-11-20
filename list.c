#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List* create_list(){
    List* list = (List*) malloc(sizeof(List));
    list->head = (Node*) malloc(sizeof(Node)); //allocate the head node
    list->tail = list->head;
    list->head->next = NULL;
    return list;
}

void insert_list(Edge* newEdge,List* list){
    list->tail->next = (Node*) malloc(sizeof(Node));
    list->tail = list->tail->next;
    list->tail->edge = newEdge;
    list->tail->next = NULL;
}

void _print_list(List* list){
    Node* aux = list->head->next;
    while(aux != NULL){
        printf("Weight: %d, Destination: %d\n", aux->edge->weight, aux->edge->destination);
        aux = aux->next;
    }
}

void free_list(List* list){
    Node* aux = NULL;
    while(aux != list->tail){
        aux = list->head->next;
        list->head->next = list->head->next->next;
        free(aux->edge); //deallocate the info inside the node
        free(aux);
    }
    free(list->head); //deallocate the head node
    free(list);
}

int empty_list(List* list){
    if(list->head == list->tail){
        return TRUE;
    } else{
    return FALSE;
    }
}
