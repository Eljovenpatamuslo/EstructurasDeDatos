#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef void** GArray;

typedef struct {
    char *nombre, *direccion, *dni;
    int edad;
} Persona;


GArray listToArray (GList lista, FuncionCopia c){
    if(glist_vacia(lista)) return NULL;
    int largo = 5;
    GArray array = malloc(sizeof(void*)*largo);
    GList aux = lista;
    for(int i = 0;aux != NULL;aux = aux->next,i++){
        if(i>largo-1){
            largo*=2;
            array = realloc(array,sizeof(void*)*largo);
        }
        array[i] = c(aux->data);
    }
    return array;
}

void* aux(void* dato){
    return dato;
}

GArray listToArrayPersona (GList lista){
    return listToArray(lista,aux);
}

int tieneA(void* dato){
    Persona* persona1 = (Persona*)dato;
    int terminar = 0;
    for(int i = 0; persona1->direccion[i] != '\n' && !terminar;i++){
        if(persona1->direccion[i] == 'a' || persona1->direccion[i] == 'A') terminar = 1;
    }
    return terminar;
}

int mayor18(void* dato){
    Persona* persona1 = (Persona*)dato;
    return persona1->edad > 18;
}

int mayorYa(void* dato){
    return tieneA(dato) && mayor18(dato);
}

GList mayores18ConA(GList lista, FuncionCopia c){
    return glist_filtrar(lista,c,mayorYa);
}

int main(){
    
    return 0;
}