#include <stdio.h>
#include <stdlib.h>
#define LARGO 6

typedef struct _Arreglo{
    int posSiguiente;
    int isLibre;
} Arreglo;

typedef struct _DNodo {
    int dato;
    void* xor;
} DNodo;

int main(){

    DNodo* nodo = malloc(sizeof(DNodo));
    DNodo* nodo2 = malloc(sizeof(DNodo));
    DNodo* nodo3 = malloc(sizeof(DNodo));
    nodo3->xor = NULL;

    nodo2->xor = NULL;

    nodo->xor = NULL;

    nodo3->dato = 3;
    nodo2->dato = 2;
    nodo->dato = 1;
    
    nodo->xor = (DNodo*)((int)nodo3 ^ (int)nodo2);
    printf("%i",((DNodo*)((int)nodo->xor ^(int)nodo2))->dato);
}