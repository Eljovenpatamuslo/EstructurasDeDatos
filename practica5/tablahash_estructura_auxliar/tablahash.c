#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include "glist.h"
#include <stdio.h>
#include "contacto.h"
/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL)
      glist_destruir((GList)tabla->elems[idx].dato,tabla->destr);

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * IMPORTANTE: La implementacion no maneja colisiones.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = glist_agregar_inicio((GList)tabla->elems[idx].dato,dato,tabla->copia);
    return;
  }
  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  else if (slist_contiene((GList)tabla->elems[idx].dato,dato,tabla->comp) != NULL) {
    tabla->elems[idx].dato = glist_buscar_y_eliminar_dato((GList)tabla->elems[idx].dato,dato,tabla->comp,tabla->destr);
    tabla->elems[idx].dato = glist_agregar_inicio((GList)tabla->elems[idx].dato,dato,tabla->copia);
    return;
  }
  // No hacer nada si hay colision.
  else {
    tabla->numElems++;
    tabla->elems[idx].dato = glist_agregar_inicio((GList)tabla->elems[idx].dato,dato,tabla->copia);
    return;
  }
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  if(slist_contiene((GList)tabla->elems[idx].dato,dato,tabla->comp) != NULL){
    return slist_contiene((GList)tabla->elems[idx].dato,dato,tabla->comp)->data;
  }
  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  if(slist_contiene((GList)tabla->elems[idx].dato,dato,tabla->comp) != NULL){
    tabla->numElems--;
    tabla->elems[idx].dato = glist_buscar_y_eliminar_dato((GList)tabla->elems[idx].dato,dato,tabla->comp,tabla->destr);
  }
  return;
}
