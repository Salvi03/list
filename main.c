#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Ringrazio Kledi (Negahertz) per avermi aiutato nel debugging

// Qesto programma contiene una struttura lista in grado di
// contenere più tipi di variabile
// Per ora solo interi e caratteri

// definisco le strutture lista e nodo
typedef struct node {
    void *val;
    char *type;
} node_t;

typedef struct list {
    struct list *prev;
    struct list *next;
    
    int index;
    node_t *val;
} list_t;

// funzione per evitare ripetizioni in un codice che ha bisogno di più liste
list_t *init() {
    list_t *list = (list_t*)malloc(sizeof(list_t));
    
    list->prev = NULL;
    list->next = NULL;
    list->val = NULL;

    // se avessi messo zero gli indici sarebbero partiti da 1
    // a causa della funzione baseAdd (vedi sotto)
    list->index = -1;

    return list;
}

// codice che viene eseguito a prescindere dal tipo di elemento che viene inserito
void baseAdd(list_t *list) {
    list_t *ptr = list;
    list_t *prev = NULL;

    int index = ptr->index;
    while (ptr->next != NULL) {   
        ptr = ptr->next;
        
        index = ptr->index;
    }

    ptr->next = (list_t*)malloc(sizeof(list_t));
    list_t *next = ptr->next;
    
    next->next = NULL;
    next->prev = ptr;
    next->val = NULL;
    next->index = ptr->index + 1;

    if (ptr->index == -1 || ptr->index == 0) {
        ptr->prev = NULL;
    }
}

void setVal(list_t *ptr, char *type) {
    ptr->val = (node_t *)malloc(sizeof(node_t));
    node_t *n = ptr->val;
    n->type = (char *)calloc(strlen(type) + 1, sizeof(char));

    int i;
    for (i = 0; i < strlen(type); i++) {
        *(n->type + i) = type[i];
    }
    *(n->type + i) = '\0';
}

// funzione per aggiungere un intero alla lista
void addInt(list_t *list, int item) {
    char c[] = "int";
    list_t *ptr = list;

    baseAdd(list);
    while (ptr->next != NULL)    
        ptr = ptr->next;
    
    setVal(ptr, c);
    node_t *n = ptr->val;

    n->val = (void*)malloc(sizeof(int));
    *((int *)n->val) = item;
}

// funzione per aggiungere un carattere alla lista
void addChar(list_t *list, char item) {
    
    char c[] = "char";
    list_t *ptr = list;

    baseAdd(list);
    while (ptr->next != NULL) {    
        ptr = ptr->next;
    }

    setVal(ptr, c);
    node_t *n = ptr->val;

    n->val = (void*)malloc(sizeof(char));
    *((char *)n->val) = item;
}

void printElement(node_t *node) {
    if (strcmp(node->type, "char") == 0)
                printf("%c\n", *((char*)node->val));
            
    if (strcmp(node->type, "int") == 0)
        printf("%d\n", *((int*)node->val));
}

void printList(list_t* list) {
    list_t* ptr = list;

    while (ptr != NULL) {
        if(ptr->val != NULL){
            node_t *node = ptr->val;
            printElement(node);
        }
        ptr = ptr->next;
    }
}

void printReversedList(list_t *list) {
    list_t *ptr = list;
    while (ptr->next != NULL)
        ptr = ptr->next;
    
    while (ptr != NULL) {
        node_t *node = ptr->val;
        printElement(node);
        ptr = ptr->prev;
    }
}

int main() {
    list_t *list = init();
    
    addChar(list, 'e');
    addChar(list, '2');
    addInt(list, 6);
    addChar(list, 'p');

    printList(list);
    printf("\n\n");
    printReversedList(list);
}