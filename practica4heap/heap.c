#include "heap.h"
#define max(a,b) (((a) > (b)) ? (a) : (b))

BHeap bheap_crear(int capacidad, FuncionComparadora comp){
    BHeap nuevoArbol = malloc(sizeof(BHeap));
    nuevoArbol->arr = malloc(sizeof(void*)*capacidad);
    nuevoArbol->capacidad = capacidad;
    nuevoArbol->comp = comp;
    nuevoArbol->ultimo = -1;
    return nuevoArbol;
}

void bheap_destruir(BHeap raiz, FuncionDestructora destroy){
    for(int i = 0;i<raiz->capacidad;i++){
        destroy(raiz->arr[i]);
    }
    free(raiz->arr);
    free(raiz);
}

int bheap_es_vacio(BHeap raiz){
    return raiz->ultimo == -1;
}

void bheap_recorrer(BHeap raiz, FuncionVisitante visit){
    for(int i = 0; i<=raiz->ultimo;i++){
        visit(raiz->arr[i]);
    }
}
BHeap bheap_insertar(BHeap raiz, void* dato){
    if(raiz->ultimo == raiz->capacidad-1){
        raiz->capacidad = raiz->capacidad * 2;
        raiz->arr = realloc(raiz->arr,sizeof(void*)*raiz->capacidad);
    }

    raiz->arr[++(raiz->ultimo)] = dato;
    for(int ind = raiz->ultimo; ind > 0 && raiz->comp(raiz->arr[ind], raiz->arr[ind/2]) ; ind/=2){
        void* t = raiz->arr[ind];
        raiz->arr[ind] = raiz->arr[ind/2];
        raiz->arr[ind/2] = t;
    }
    return raiz;
}
BHeap bheap_eliminar(BHeap raiz, void* dato){
    int i=0;
    for(;i<=raiz->ultimo && raiz->comp(raiz->arr[i],dato);i++);
    printf("%i\n",*((int*)raiz->arr[i]));
    raiz->arr[i] = raiz->arr[raiz->ultimo];
    raiz->ultimo--;
    if(raiz->arr[i] < raiz->arr[i/2]){
        for(int ind = raiz->ultimo; ind > 0 && raiz->comp(raiz->arr[ind], raiz->arr[ind/2]) ; ind/=2){
        void* t = raiz->arr[ind];
        raiz->arr[ind] = raiz->arr[ind/2];
        raiz->arr[ind/2] = t;
    }    
    }else{

    }

    return raiz;
}

BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopia copiar, FuncionComparadora comp){
    BHeap arbol = bheap_crear(largo,comp);
    qsort(arr,largo,sizeof(void*),comp);     
    arbol->arr = arr;
    arbol->capacidad = largo;
    arbol->ultimo = largo-1;
    arbol->comp = comp;
    return arbol;
}