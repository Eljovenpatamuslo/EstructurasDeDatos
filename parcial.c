#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct _GNodo {
    void * dato ;
    struct _GNodo * sig ;
    } GNodo ;
    typedef struct {
    GNodo * primero ;
    GNodo * ultimo ;
    } GList ;
    typedef void (* FuncionDestructora ) ( void * dato ) ;
    typedef void * (* FuncionCopia ) ( void * dato ) ;
    typedef void (* FuncionVisitante ) ( void * dato ) ;
    typedef void * (* FuncionTransformar ) ( void * dato ) ;
    GList glist_crear () {
    GList lista ;
    lista . primero = NULL ;
    lista . ultimo = NULL ;
    return lista ;
    }
    GList glist_agregar_final ( GList lista , void * dato , FuncionCopia copia ) {
    GNodo * nuevo = malloc ( sizeof ( GNodo ) ) ;
    nuevo -> dato = copia ( dato ) ;
    nuevo -> sig = NULL ;
    if ( lista . primero == NULL )
    lista . primero = nuevo ;
    else
    lista . ultimo -> sig = nuevo ;
    lista . ultimo = nuevo ;
    return lista ;
    }
    void glist_destruir ( GList lista , FuncionDestructora destroy ) {
    GNodo * temp ;
    for ( GNodo * nodo = lista . primero ; nodo != NULL ; ) {
    temp = nodo ;
    nodo = nodo -> sig ;
    destroy ( temp -> dato ) ;
    free ( temp ) ;
    }
    }

GList glist_map ( GList lista , FuncionTransformar f , FuncionCopia c ){
    GList listaMap = glist_crear();
    for(GNodo* aux = lista.primero; aux != NULL ;aux = aux->sig){
        listaMap = glist_agregar_final(listaMap, f(aux->dato),c);
    }
    return listaMap;
}

void* stringMayuscula(void* str){
    char* string1 = (char*)str;
    int len = strlen(string1);
    char* newString = malloc(sizeof(char)*len+1);
    for(int i = 0;string1[i] != '\0';i++){
        newString[i] =  tolower(string1[i]);
    }
    newString[len] = '\0';
    return newString;
}