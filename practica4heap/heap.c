#include "heap.h"

#define RIGHT(i) (2 * (i + 1))
#define LEFT(i) ((2 * i) + 1)
#define PARENT(i) ((i-1)/2)

#define HEAP_SIZE 1024

void swap(void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
}

BHeap bheap_crear(FuncionComparadora comp, FuncionCopia copy,FuncionDestructora destr){
    BHeap bHeap = malloc(sizeof(struct _BHeap));
    bHeap->arr = malloc(sizeof(void*)*HEAP_SIZE);
    bHeap->capacidad = HEAP_SIZE;
    bHeap->comp = comp;
    bHeap->destr = destr;
    bHeap->copy = copy;
    bHeap->ultimo = -1;
    return bHeap;
}

void bheap_destruir(BHeap bHeap){
    bheap_recorrer(bHeap->destr, bHeap);
    free(bHeap->arr);
    free(bHeap);
}

int bheap_es_vacio(BHeap bHeap){
    return bHeap->ultimo == -1;
}

void bheap_recorrer(FuncionVisitante visit, BHeap bHeap){
    for(int i = 0; i <= bHeap->ultimo; i++){
        visit(bHeap->arr[i]);
    }
}

void flotar(BHeap bHeap, int i){
    
    /* COMPLETAR */
    while (i != 0 && bHeap->comp(bHeap->arr[i], bHeap->arr[PARENT(i)]) > 0) {
        swap(&bHeap->arr[i], &bHeap->arr[PARENT(i)]);
        i = PARENT(i);
    }

}

void bheap_insertar(void* data,BHeap bHeap){
    if(bHeap->ultimo + 1 == bHeap->capacidad){ 
            bHeap->arr = realloc(bHeap->arr, sizeof(void*)*bHeap->capacidad*2);
        bHeap->capacidad *= 2;
    }
    // Insertamos el elemento al final del Heap
    bHeap->arr[++bHeap->ultimo] = bHeap->copy(data);
    // Flotamos el elemento hasta su posición final
    flotar(bHeap, bHeap->ultimo);
}  

void hundir(BHeap bHeap, int i){
    int new_i = i;
    /* COMPLETAR */
    if (LEFT(i) <= bHeap->ultimo && bHeap->comp(bHeap->arr[LEFT(i)], bHeap->arr[new_i]) > 0)
        new_i = LEFT(i);

    if (RIGHT(i) <= bHeap->ultimo && bHeap->comp(bHeap->arr[RIGHT(i)], bHeap->arr[new_i]) > 0)
        new_i = RIGHT(i);

    if (new_i != i) {
        swap(&bHeap->arr[i], &bHeap->arr[new_i]);
        hundir(bHeap, new_i);
    }

}


void bheap_eliminar(void* data, BHeap bHeap){
    int pos = -1;
    int i = 0;

    // Buscamos la primera aparicion del elemento
    while (pos == -1 && i <= bHeap->ultimo) {

        if (bHeap->comp(data, bHeap->arr[i]) == 0) {
            pos = i;
        }

        i++;

    }

    if(pos == -1){
        printf("El elemento no se encuentra en el arbol\n");
        return;
    }

    //Si el elemento estaba en el arbol, lo quitamos y lo reemplazamos por el ultimo.
    void* elem = bHeap->arr[pos];
    bHeap->arr[pos] = bHeap->arr[bHeap->ultimo--];

    // Destruimos el dato
    bHeap->destr(elem);

    // Ubicamos el dato segun corresponda
    if (pos > 0 && bHeap->comp(bHeap->arr[pos], bHeap->arr[PARENT(pos)]) > 0) {
        flotar(bHeap, pos);
    } 
    else {
        hundir(bHeap, pos);
    }
}

BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destr){

    BHeap bHeap = malloc(sizeof(struct _BHeap));
    bHeap->comp = comp;
    bHeap->copy = copy;
    bHeap->destr = destr;
    bHeap->capacidad = largo;
    bHeap->ultimo = largo-1;
    bHeap->arr = arr;
    
    // Convertimos en bheap. Notar que la ultima mitad del array son todas hojas
    for(int i = largo / 2; i >= 0; i --){
        hundir(bHeap, i);
    }
    return bHeap;
}

void* dummy_copy(void* dato){
    return dato;
}

void dummy_destr(void* dato){
    (void) dato;
    return;
}

void* bheap_pop(BHeap bHeap){
    void* max = bHeap->arr[0];
    // Reemplazamos la raiz por el ultimo
    bHeap->arr[0] = bHeap->arr[bHeap->ultimo--];
    // Hundimos la nueva raiz hasta su posición final
    hundir(bHeap, 0);
    return max;
}

void heapSort(void** arr, int largo, FuncionComparadora comp){
    BHeap bHeap = bheap_crear_desde_arr(arr, largo, comp, dummy_copy, dummy_destr);
    for(int i = largo - 1; i >= 0; i--){
        void* max = bheap_pop(bHeap);
        bHeap->arr[i] = max;
    }
    free(bHeap);
}

/*#define max(a,b) (((a) > (b)) ? (a) : (b))

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
}*/