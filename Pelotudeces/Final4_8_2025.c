#include <stdio.h>
#include <stdlib.h>

typedef struct _GNodo{
    int fila;
    int columna;
    struct _GNodo* next;
}GNodo;

typedef struct List_{
    GNodo* primero;
}GList;


GList crearMatriz(){
    GList lista;
    lista.primero = NULL;
    return lista;
}

void destroy(GList* lista){
    GNodo* delete = lista->primero;
    GNodo* aux;
    while(delete != NULL){
        aux = delete;
        delete = delete->next;
        free(aux);
    }
}

void insertar(GList* matriz, int i, int j) {
    GNodo *nuevo = malloc(sizeof(GNodo));
    nuevo->fila = i;
    nuevo->columna = j;
    nuevo->next = matriz->primero;
    matriz->primero = nuevo;
}

void eliminar(GList* matriz, int i, int j) {
    GNodo *actual = matriz->primero;
    GNodo *anterior = NULL;

    while (actual != NULL) {
        if (actual->fila == i && actual->columna == j) {
            if (anterior == NULL) {
                matriz->primero = actual->next;
            } else {
                anterior->next = actual->next;
            }
            free(actual);
            return;
        }
        anterior = actual;
        actual = actual->next;
    }
}

int esSimetrica(GList matriz) {
    GNodo *actual = matriz.primero;

    while (actual != NULL) {
        GNodo *buscador = matriz.primero;
        int encontrado = 0;

        while (buscador != NULL) {
            if (buscador->fila == actual->columna && buscador->columna == actual->fila) {
                encontrado = 1;
                break;
            }
            buscador = buscador->next;
        }

        if (!encontrado) {
            return 0; // No es simétrica
        }

        actual = actual->next;
    }

    return 1; // Es simétrica
}

int rKleen(GList matriz, int nodo, int numNodos) {
    // Crear un arreglo para marcar los nodos visitados
    int visitados[numNodos];
    for (int i = 0; i < numNodos; i++) {
        visitados[i] = 0;
    }

    // Cola para manejar la exploración (BFS)
    int cola[numNodos];
    int inicio = 0, fin = 0;

    // Marcar el nodo inicial como visitado y agregarlo a la cola
    visitados[nodo] = 1;
    cola[fin++] = nodo;

    int alcanzables = 0;
    // BFS
    while (inicio < fin) {
        int actual = cola[inicio++];
        alcanzables++;

        // Recorrer las relaciones del nodo actual
        GNodo *temp = matriz.primero;
        while (temp != NULL) {
            printf("%i %i \n",temp->fila,temp->columna);
            if (temp->fila == actual && !visitados[temp->columna]) {
                visitados[temp->columna] = 1;
                cola[fin++] = temp->columna;
            }
            temp = temp->next;
        }
    }

    // Devolver el número de nodos alcanzables
    return alcanzables - 1; // Excluimos el nodo inicial
}

int main() {
    GList matriz = crearMatriz();

    // Inserciones
    insertar(&matriz, 0, 1);
    insertar(&matriz, 1, 0);
    insertar(&matriz, 2, 0);
    insertar(&matriz, 3, 2);
    insertar(&matriz, 2, 1);
    insertar(&matriz, 2, 2);
    insertar(&matriz, 2, 3);
    insertar(&matriz, 2, 4);

    // Tamaño del grafo (número de nodos)
    int numNodos = 5;

    // Calcular r-kleen para el nodo 0
    int nodo = 3;
    printf("El nodo %d está conectado con %d nodos (directa o indirectamente).\n", nodo, rKleen(matriz, nodo, numNodos));
    destroy(&matriz);
    return 0;
}