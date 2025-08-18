#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


//Crea una nueva tabla hash vacia, con la capacidad dada.


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

//Retorna el numero de elementos de la tabla.

int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }


//Retorna la capacidad de la tabla.
 
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }


//Destruye la tabla.

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


//Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.

void tablahash_insertar(TablaHash tabla, void *dato) {

  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  int idx_ocupado = -1;

  for(;tabla->elems[idx].dato != NULL && tabla->comp(tabla->elems[idx].dato,dato) != 0 ; idx = (idx+1) % tabla->capacidad){
    if(tabla->elems[idx].ocupado == 0 && idx_ocupado == -1){
      idx_ocupado = (int)idx;
    }
  }
  if(tabla->elems[idx].dato != NULL){//encontró un dato idéntico, sobreescribir
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = tabla->copia(dato);
    if(tabla->elems[idx].ocupado == 0){
      tabla->numElems++;
      tabla->elems[idx].ocupado = 1;
    }
  }
  else if(idx_ocupado == -1){ //se detuvo en NULL y idx_ocupado == -1, no hay valores eliminados, escribir en donde estoy
    tabla->numElems++;
    tabla->elems[idx].dato = tabla->copia(dato);
    tabla->elems[idx].ocupado = 1;
  }
  else{//se detuvo en NULL y idx_ocupado != -1 , hay valores eliminados, inserto en el primero de ellos
    tabla->destr(tabla->elems[idx_ocupado].dato);
    tabla->numElems++;
    tabla->elems[idx_ocupado].dato = tabla->copia(dato);
    tabla->elems[idx_ocupado].ocupado = 1;
  }

  float factor_de_carga = (float)tabla->numElems / (float)tabla->capacidad;
    if (factor_de_carga >= 0.7)
      tablahash_redimensionar(tabla);
}


//Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
//buscado no se encuentra en la tabla.
 

void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar NULL si la casilla estaba vacia.
    if (tabla->elems[idx].dato == NULL)
        return NULL;
    // Si la posicion está ocupada, vamos a recorrer la tabla hasta encontrarlo (o no!)
    else{
        unsigned h = idx;
        for(;tabla->elems[h].dato != NULL && tabla->comp(tabla->elems[h].dato,dato) != 0;h = (h+1)%tabla->capacidad);
        
        if (tabla->elems[h].dato != NULL && tabla->elems[h].ocupado == 1)
          return tabla->elems[h].dato;
        else{
          return NULL;
        }
    }
}





//Elimina el dato de la tabla que coincida con el dato dado.

void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return;
  // Vaciar la casilla si hay coincidencia.
  else{
        unsigned h = idx;
        for(;tabla->elems[h].dato != NULL && tabla->comp(tabla->elems[h].dato,dato) != 0;h = (h+1)%tabla->capacidad);
        
        if (tabla->elems[h].dato == NULL)
          return;
        else{
          if(tabla->elems[h].ocupado == 1){
            tabla->elems[h].ocupado = 0;
            tabla->numElems--;
          }
          return;
        }
  }
}
void* copydummy (void* dato){
  return dato;
}

void tablahash_redimensionar(TablaHash tabla){
    
  int vieja_capacidad = tabla->capacidad;
  tabla->capacidad*=2;

  CasillaHash* vieja_tabla = tabla->elems;
  tabla->elems = malloc(sizeof(CasillaHash) * tabla->capacidad);

  assert(tabla->elems != NULL);
  tabla->numElems = 0;

  for (unsigned int i = 0; i < tabla->capacidad;i++){
    tabla->elems[i].dato = NULL;
    tabla->elems[i].ocupado = 0;
  }
  FuncionCopiadora buenaCopia = tabla->copia;
  tabla->copia = copydummy;

  for (int i = 0; i < vieja_capacidad;i++){
    if (vieja_tabla[i].dato != NULL){
      tablahash_insertar(tabla,vieja_tabla[i].dato);
      }
  }

  tabla->copia = buenaCopia;
  free(vieja_tabla);
}
