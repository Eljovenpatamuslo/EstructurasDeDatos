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
    if (bHeap->ultimo < 0) {
        return NULL; // El heap está vacío, no hay nada que eliminar
    }

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

void  swap_int(int* x, int* y) {
    int  temp = *x;
    *x = *y;
    *y = temp;
}


//  Hunde el  elemento  en la  posicion  pos  del  arreglo  hasta  que  este  cumpla  lacondicion  de max -heap. n es la  cantidad  de  elementos  del  arreglo
void  hundir2(int* arr , int n,int pos) {
    int  max_pos = pos;
    if (LEFT(pos) < n && arr[LEFT(pos)] > arr[max_pos ])
      max_pos = LEFT(pos);
    if (RIGHT(pos) < n && arr[RIGHT(pos)] > arr[max_pos ])
      max_pos = RIGHT(pos);
    if (max_pos  != pos) {
        swap_int (&arr[pos], &arr[max_pos ]);
        hundir2(arr , n,max_pos);
    }
}

void heapSort2(int* arr, int largo){
    for(int i = largo /2 ; i>= 0 ; i--){
        hundir2(arr,i,largo);
    }
    for(int i = largo - 1; i >= 0; i--){
        swap_int(&arr[0],&arr[i]);
        hundir2(arr,i,0);

    }
}

//crear una Priority queue
PriorityQueue cola_prioridad_crear(FuncionComparadora comp, FuncionCopia copy,FuncionDestructora destr){
    return bheap_crear(comp,copy,destr);
}

void cola_prioridad_destruir(PriorityQueue pq){
    bheap_destruir(pq);
}

//retorne 1 si la cola esta vacia y 0 en caso contrario
int cola_prioridad_es_vacia(PriorityQueue pq){
    return(pq->ultimo < 0);
}
//  inserta un elemento en la cola con una determinada prioridad.
void cola_prioridad_insertar( void* dato, PriorityQueue pq)
{
    bheap_insertar(dato,pq);
}

// retorna el elemento prioritario de la cola
void* cola_prioridad_maximo(PriorityQueue pq)
{
   if (pq->ultimo < 0) {
        return NULL; // No hay elementos en el heap
    }
    return pq->arr[0];
}

//elimina el elemento prioritario de la cola
void cola_prioridad_eliminar_maximo(PriorityQueue pq)
{
    bheap_pop(pq);
}