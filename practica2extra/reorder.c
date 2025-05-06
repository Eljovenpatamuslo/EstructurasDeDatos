#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _GNode {
    int data;
    struct _GNode *next;
} GNode;
  
typedef GNode* GList;

GList glist_crear() { return NULL; }

GList glist_agregar_inicio(GList list, int data) {
    GNode *newNode = malloc(sizeof(GNode));
    assert(newNode != NULL);
    newNode->next = list;
    newNode->data = data;
    return newNode;
}

GList reorder(GList list){
    if(list == NULL) return NULL;
    if(list->next == NULL || list->next->next == NULL) return list;
    GList aux = list;
    for(; aux->next->next != NULL; aux = aux->next);
    GList basura = list->next;
    GList basura2 = aux->next;
    list->next = aux->next;//1->6
    aux->next = NULL;//5-->NULL
    basura2->next = reorder(basura);
    return list;
}
// 1 2
// 1 2 3 --> 1 3 2
// 1 2 3 4
// 1 2 3 4 5 6 7 --> 1 7 (2 3 4 5 6) -> 1 7 2 6 (3 4 5) -> 1 7 2 6 3 5 (4)
// 1 6 2 3 4 5 NULL 

void glist_recorrer(GList list) {
    for (GNode *node = list; node != NULL; node = node->next)
      printf("%i",node->data);
  }
//Implementar una cola con 2 pilas
int main(){
    GList lista = glist_crear();
    lista = glist_agregar_inicio(lista,7);
    lista = glist_agregar_inicio(lista,6);
    lista = glist_agregar_inicio(lista,5);

    lista = glist_agregar_inicio(lista,4);

    lista = glist_agregar_inicio(lista,3);
    lista = glist_agregar_inicio(lista,2);
    lista = glist_agregar_inicio(lista,1);

    lista = reorder(lista);
    glist_recorrer(lista);

}