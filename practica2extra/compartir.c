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

GList nodo_compartido(GList lista1, GList lista2){
    GList aux = lista1;
    int bandera = 0;
    for(; aux != NULL && !bandera; aux = aux->next){
        for(GList aux2 = lista2; aux2 != NULL && !bandera; aux2 = aux2->next){
            if(aux->next == aux2->next) bandera = 1; 
        }        
    }
    return aux;
}

int main(){
    GList lista1 = glist_crear();
    GList lista2 = glist_crear();

    lista1 = glist_agregar_inicio(lista1,9);
    lista1 = glist_agregar_inicio(lista1,8);
    lista1 = glist_agregar_inicio(lista1,7);
    GList aux = lista1;
    lista1 = glist_agregar_inicio(lista1,3);
    lista1 = glist_agregar_inicio(lista1,2);
    lista1 = glist_agregar_inicio(lista1,1);
    lista2 = aux;
    lista2 = glist_agregar_inicio(lista2,6);
    lista2 = glist_agregar_inicio(lista2,5);

    printf("%i",nodo_compartido(lista1,lista2)->data);
    
}