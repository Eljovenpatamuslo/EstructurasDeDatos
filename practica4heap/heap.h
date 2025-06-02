#include <stdio.h>
#include <stdlib.h>

typedef int (*FuncionComparadora)(const void *dato1,const void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _BHeap {
    void **arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
} *BHeap;

BHeap bheap_crear(int capacidad, FuncionComparadora comp);
void bheap_destruir(BHeap raiz, FuncionDestructora destroy);
int bheap_es_vacio(BHeap raiz);
void bheap_recorrer(BHeap raiz, FuncionVisitante visit);
BHeap bheap_insertar(BHeap raiz, void* dato);
BHeap bheap_eliminar(BHeap raiz, void* dato);

BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopia copiar, FuncionComparadora comp);