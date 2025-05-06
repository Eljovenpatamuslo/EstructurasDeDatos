#include <stdio.h>
#include <stdlib.h>

typedef struct _GNode {
    int data;
    struct _GNode *next;
} GNode;
  
typedef GNode* GList;

int glist_contiene(GList list, int data){
    GList aux = list;
    for (; aux != NULL && aux->data != data; aux = aux->next);
    return aux != NULL;
}

GList glist_agregar_inicio(GList list, int data) {
    GNode *newNode = malloc(sizeof(GNode));
    assert(newNode != NULL);
    newNode->next = list;
    newNode->data = data;
    return newNode;
}

GList chequear_ciclo(GList list){
    GList list2 = crear_list();
    GList aux = list;
    for(;!glist_contiene(list2,aux->data) && aux != NULL;list2 = glist_agregar_inicio(list2,aux->data),aux = aux->next);
    if(aux == NULL) return NULL;
    return aux;
}

int main(){

    return 0;
}