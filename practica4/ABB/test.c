#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Casos de prueba para arboles de busqueda binaria generales
 */

#define N_PALABRAS 16

static void *copiar_cadena(void *dato) {
  char *str = malloc(sizeof(char) * (strlen(dato) + 1));
  assert(str != NULL);
  strcpy(str, dato);
  return str;
}
static int comparar_cadena(void *dato1, void *dato2) {
  return strcmp(dato1, dato2);
}
static void destruir_cadena(void *dato) {
  free(dato);
}


static void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("\"%s\" ", (char *)dato);
}


static void *f_copiar(void *dato) {
  int *copia = malloc(sizeof(int));
  *copia = *((int *) dato);
  return copia; 
}

static int f_comp(void *dato1, void *dato2) {
  return *((int *)dato1) - *((int *)dato2);
}

static void f_destruir (void *dato) {
  free(dato);
}

static void f_recorrer(void *dato, __attribute__((unused)) void *extra) {
  printf("%d ", *((int *)dato));
}

int main() {

  char *palabras[N_PALABRAS] = {"gato",      "perro",    "casa",     "persona",
                                "parque",    "arbol",    "edificio", "calle",
                                "argentina", "santa fe", "rosario",  "unr",
                                "edya",      "farmacia", "tiempo",   "celular"};

  // Creamos un arbol vacio y le insertamos las palabras
  BSTree arbol = bstee_crear();
  for (int i = 0; i < N_PALABRAS; i++)
    arbol = bstree_insertar(arbol, palabras[i], copiar_cadena, comparar_cadena);

  // Imprimir el arbol inorden (alfabetico)
  printf("Recorrido inorden: ");
  bstree_recorrer(arbol, BTREE_RECORRIDO_IN, imprimir_cadena, NULL);
  puts("");

  // Buscar elementos
  assert(bstree_buscar(arbol, "farmacia", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "santa fe", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "persona", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "unr", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "argentina", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "telefono", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "mail", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "parques", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "EDyA1", comparar_cadena) == 0);

  BSTree arbol1 = bstree_eliminar(arbol,"unr", comparar_cadena, destruir_cadena);
  bstree_recorrer(arbol1, BTREE_RECORRIDO_IN, imprimir_cadena, NULL);

  // Destruir arbol
  bstree_destruir(arbol, destruir_cadena);

  BSTree arbol2 = bstee_crear();

    /* Caso base para el árbol vacío. */
  assert(bstree_k_esimo_menor(arbol2, 0) == NULL);
  int j;
  /* Creo un arbol de la forma
              0
            /   \
          -2     1
         /   \    \
       -3    -1    2
                    \
                     3
                    / \
               números random */
  j = 0;
  arbol2= bstree_insertar(arbol2, &j, f_copiar, f_comp);
  j = -2;
  arbol2 = bstree_insertar(arbol2, &j, f_copiar, f_comp);
  j = -1;
  arbol2 = bstree_insertar(arbol2, &j, f_copiar, f_comp);
  j = -3;
  arbol2 = bstree_insertar(arbol2, &j, f_copiar, f_comp);
  for (int i = 1; i < 4; i++) 
    arbol2 = bstree_insertar(arbol2, &i, f_copiar, f_comp);
  for (int i = 0; i < 15; ++i) {
    int i = rand() % 100;
    arbol2 = bstree_insertar(arbol2, &i, f_copiar, f_comp);
  }
  /* Veo en pantalla el orden de los elementos. */
  puts("Recorrido IN");
  bstree_recorrer(arbol2, BTREE_RECORRIDO_IN, f_recorrer, NULL);
  puts("");
  /* Test de bstree_k_esimo_menor en diferentes casos. */
  assert( *((int *)bstree_k_esimo_menor(arbol2, 0)) == -3);  
  assert( *((int *)bstree_k_esimo_menor(arbol2, 1)) == -2);  
  assert( *((int *)bstree_k_esimo_menor(arbol2, 3)) == 0); 
  assert( *((int *)bstree_k_esimo_menor(arbol2, 2)) == -1); 
  
  
  assert( *((int *)bstree_k_esimo_menor(arbol2, 5)) == 2);
  assert( bstree_k_esimo_menor(arbol2, 30) == NULL);  
  assert( bstree_k_esimo_menor(arbol2, -1) == NULL);  


  bstree_destruir(arbol2, f_destruir);

  return 0;
}
