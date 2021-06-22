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
    if(list->head == list->tail){
        printf("Vazia!\n");
    } else{
        while(aux != NULL){
            printf("Weight: %d, Origin: %d, Destination: %d\n",aux->edge->weight, aux->edge->origin, aux->edge->destination);
            aux = aux->next;
        }
    }
}

void free_list(List* list){
    Node* aux = NULL;
    if(list->tail = list->head){ //case for empty lists
        free(list->head);
        free(list);
        return;
    }
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

void remove_list(List* list, int origin, int destination){
    Node* aux = list->head;
    Node* removed;
    int bol = 0;
    /* runs the list trying to find a matching edge, if it finds one will remove
    it from the list */
    while(aux != list->tail){
        if((aux->next->edge->origin == origin && aux->next->edge->destination == destination) ||
            (aux->next->edge->origin == destination && aux->next->edge->destination == origin)){
                removed = aux->next;
                if(aux->next == list->tail){ //case for the last element of the list
                    list->tail = aux;
                    list->tail->next = NULL;
                } else{
                    aux->next = aux->next->next;
                }
                free(removed->edge); //deallocating edge's info
                free(removed); //deallocating edge
                bol = 1;      
        }
        /* if we remove some edge from the list it will affect the way we runs it, so
        if we remove we dont need to go for the next edge, because we already made it
        removing the one between them */
        if(bol == 0){
            aux = aux->next;
        }
        bol = 0; //reseting bol
    }
}
