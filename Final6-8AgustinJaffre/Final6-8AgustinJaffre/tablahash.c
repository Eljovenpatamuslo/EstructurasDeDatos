#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
  int ocupado;
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
    tabla->elems[idx].ocupado = 0;
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
      tabla->destr(tabla->elems[idx].dato);

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
  // Insertar el dato si la casilla no esta ocupada.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = tabla->copia(dato);
    tabla->elems[idx].ocupado = 1;
  }
  //Si la casilla tiene algun dato,itero por la tabla hasta encontrar valor no ocupado
  else{   
    unsigned h = idx;
    for(;tabla->elems[h].ocupado != 0 && tabla->comp(tabla->elems[h].dato,dato) != 0;h = (h+1) % tabla->capacidad);
    if(tabla->elems[h].ocupado == 1){//dato identico, sobreescribir
      tabla->destr(tabla->elems[h].dato);
      tabla->elems[h].dato = tabla->copia(dato);
    }
    else{//dato no ocupado
      if(tabla->elems[h].dato == NULL){//no hay dato
      tabla->elems[h].dato = tabla->copia(dato);
      tabla->elems[h].ocupado = 1;
      tabla->numElems++;
    }else{//dato existente
      tabla->destr(tabla->elems[h].dato);
      tabla->elems[h].dato = tabla->copia(dato);
      tabla->elems[h].ocupado = 1;
      tabla->numElems++;
    }
    }
    
    }
  float factor_carga = (float)tabla->numElems / (float)tabla->capacidad;
  if(factor_carga > 0.75){
    tablahash_redimensionar(tabla);
  }

} 

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL){
    return NULL;
  }
  // Itero por los elementos de la tabla hasta encontrar el elemento o llegar a NULL
  else{
    unsigned h = idx;
    for (;tabla->elems[h].dato != NULL && tabla->comp(tabla->elems[h].dato,dato) != 0;h = (h+1) % tabla->capacidad);
    if(tabla->elems[h].ocupado == 0){
      return NULL; // el dato no ocupa espacio o no existe
    }
    else{//el dato ocupa espacio --> existe
      return tabla->elems[h].dato;
    }
  }
  // Retornar NULL en otro caso.
    return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return;
  // Si la casilla no esta vacia itero por los elementos de la tabla hasta encontrar el dato
  else{
    unsigned h = idx;
    for (;tabla->elems[h].dato != NULL && tabla->comp(tabla->elems[h].dato,dato) != 0;h = (h+1) % tabla->capacidad);
    if (tabla->elems[h].dato == NULL)return; // dato no esta en la tabla
    else{//si el dato fue encontrado
      if (tabla->elems[h].ocupado == 1){//y esta ocupando en la tabla
        tabla->numElems--;
        tabla->elems[h].ocupado = 0;
        return;
      }
      return;//y el elemento no esta ocupando espacio
    }
  }
}
void tablahash_redimensionar(TablaHash tabla){
  unsigned vieja_capacidad = tabla->capacidad;
  tabla->capacidad *= 2;


  CasillaHash* vieja_tabla = tabla->elems;

  tabla->elems = malloc(sizeof(CasillaHash) * tabla->capacidad);
  assert(tabla->elems != NULL);

  //Inicilizamos la tabla hash nueva
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].ocupado = 0;
  }
  tabla->numElems = 0;

  //iteramos por vieja_tabla y rehasheamos los elementos
  for(unsigned idx = 0; idx < vieja_capacidad; ++idx){
    if(vieja_tabla[idx].dato != NULL){
      tablahash_insertar(tabla, vieja_tabla[idx].dato);
      tabla->destr(vieja_tabla[idx].dato);

    }
  }
  //Una vez iterados todos los elementos de la vieja_tabla , se libera
  free(vieja_tabla);
}
