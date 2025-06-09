#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define NUM 7
void swap(void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
}

// Particion de Lomuto
// Devuelve cant de elementos ≤ p
int particionar(void** A, int start, int end) {
    void* p = A[end]; // Último elemento como pivote
    int j = start; // Marca el límite de los elementos menores al pivote
    for (int i = start; i < end; i++) {
        if (*(int*)A[i] < *(int*)p) {
            swap(&A[i], &A[j]);
            j++;
        }
    }
    // Coloca el pivote en su posición final
    swap(&A[j], &A[end]);
    return j;
}

void qsort_new(void** arr, int start, int end) {
    if (end - start  > 1) return; // Condición de salida: rango inválido o de tamaño 1
    int pos = particionar(arr, start, end);

    qsort_new(arr, start, pos - 1); // Ordenar sublista izquierda
    qsort_new(arr, pos + 1, end);   // Ordenar sublista derecha
}

// Quickselect para encontrar el k-ésimo elemento
int quickselect(void** A, int start, int end, int k) {
    if (start == end) {
        // Caso base: solo un elemento
        return *(int*)A[start];
    }

    // Particionar el arreglo
    int pos = particionar(A, start, end);

    if (pos == k) {
        // Hemos encontrado el k-ésimo elemento
        return *(int*)A[pos];
    } else if (pos > k) {
        // Buscar en la sublista izquierda
        return quickselect(A, start, pos - 1, k);
    } else {
        // Buscar en la sublista derecha
        return quickselect(A, pos + 1, end, k);
    }
}

int main(){
    void** arr = malloc(sizeof(void*) * NUM);
    assert(arr);

    srand(time(NULL));

    for (int i = 0; i < NUM; i++) {
        arr[i] = malloc(sizeof(int));
        *(int*)arr[i] = rand() % ((NUM*10) + 1); 
        printf("%i\n",*(int*)arr[i]);

    }

    //k-esimo valor a encontrar
    int k = 4;
    // Encontrar el k-ésimo elemento
    int resultado = quickselect(arr, 0, NUM-1,k);
    printf("El %d-ésimo elemento en el arreglo ordenado es: %d\n", k + 1, resultado);

    qsort_new(arr,0,NUM-1);
    printf("Resultado final: \n");
    for(int i=0; i<NUM; i++){
        printf("%i\n",*(int*)arr[i]);
    }

    for (int i = 0; i < NUM; i++) {
        free(arr[i]);
    }
    free(arr);
}