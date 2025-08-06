#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct _Cliente{
    char* nombre;
    char* apellido;
    char* direccion;
    int dni_p;
}Cliente;

typedef struct _Consumo{
    char* fecha;
    int monto;
    int dni_c;
}Consumo;

typedef int (*FuncionComparadora) (Consumo, Consumo);


typedef struct _BST_Nodo{
    Consumo cons;
    struct _BST_Nodo *izq, *der;
}_BST_Nodo;

typedef struct _BST_Nodo *Bstree;

Bstree crear_bst(){
    return NULL;
}

int bstree_es_vacio(Bstree arbol){return (arbol == NULL);}

Bstree insertar (Bstree arbol, Consumo dato, FuncionComparadora comp){
    if(arbol == NULL){ //Inserto un dato en el nuevo nodo
        Bstree nuevonodo = malloc(sizeof(_BST_Nodo));
        nuevonodo->cons = dato;
        nuevonodo->izq = NULL;
        nuevonodo->der = NULL;
        return nuevonodo;
    }

    if(comp(arbol->cons,dato) <= 0) //la fecha es mayor o igual a la raiz del arbol
        arbol->der = insertar (arbol->der, dato, comp);
    else{ //la fecha es menor que la de la raiz del arbol
        arbol->izq = insertar (arbol->izq, dato, comp);
    }
    return arbol;
}

void destruir(Bstree arbol){
    if(arbol != NULL){
        destruir(arbol->izq);
        destruir(arbol->der);
        free(arbol);
    }
}

typedef struct _CasillaHash{
    Consumo dato;
    int ocupado;
}CasillaHash;

typedef struct _TablaHash{
    CasillaHash* elems;
    int numElems;
    int capacidad;
}_TablaHash;

typedef struct _TablaHash* TablaHash;
void tablahash_redimensionar(TablaHash tabla, FuncionComparadora comp);

TablaHash tablahash_crear(unsigned capacidad) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].ocupado = 0;
  }

  return tabla;
}


//Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.

void tablahash_insertar(TablaHash tabla, Consumo dato, FuncionComparadora comp) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = dato.dni_c % tabla->capacidad;
  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].ocupado == 0) {
    tabla->numElems++;
    tabla->elems[idx].dato = dato;
    tabla->elems[idx].ocupado = 1;
  }
   // Si el lugar ya está ocupado, recorremos la tabla hasta encontrar una posicion vacía
  else{
    
    unsigned h = idx;
    for(;tabla->elems[h].ocupado == 1;h = (h+1)%tabla->capacidad);
    if (tabla->elems[h].ocupado == 0){
        tabla->elems[h].dato = dato;
        tabla->elems[h].ocupado = 1;
        tabla->numElems++;
    }
  }
  float factor_de_carga = (float)tabla->numElems / (float)tabla->capacidad;
  if (factor_de_carga >= 0.7)
    tablahash_redimensionar(tabla, comp);
}

void tablahash_redimensionar(TablaHash tabla, FuncionComparadora comp){
    
  int vieja_capacidad = tabla->capacidad;
  tabla->capacidad*=2;

  CasillaHash* vieja_tabla = tabla->elems;
  tabla->elems = malloc(sizeof(CasillaHash) * tabla->capacidad);

  assert(tabla->elems != NULL);
  tabla->numElems = 0;

  for (unsigned int i = 0; i < tabla->capacidad;i++){
    tabla->elems[i].ocupado = 0;
  }

  for (int i = 0; i < vieja_capacidad;i++){
    if (vieja_tabla[i].ocupado == 1){
      tablahash_insertar(tabla,vieja_tabla[i].dato,comp);
      }
  }
  free(vieja_tabla);
}


int main(){
    




    return 0;
}