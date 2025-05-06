#include "contacto.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  GList lista = glist_crear();
  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  for (int i = 0; i < 6; ++i) {
    lista =
        glist_agregar_inicio(lista, contactos[i], (FuncionCopia)contacto_copia);
    contacto_destruir(contactos[i]);
  }

  GList lista2 = glist_crear();
  Contacto *contactos2[6];
  contactos2[0] = contacto_crear("pata", "3412695452", 61);
  contactos2[1] = contacto_crear("jaffre", "3412684759", 60);
  contactos2[2] = contacto_crear("conga", "3415694286", 32);
  contactos2[3] = contacto_crear("aquilia", "3416259862", 29);
  contactos2[4] = contacto_crear("ayrton", "3416874594", 59);
  contactos2[5] = contacto_crear("bramucci", "3416894526", 64);

  Contacto *contacto = contacto_crear("caca", "3412695452", 61);

  for (int i = 0; i < 6; ++i) {
    lista2 =
        glist_agregar_inicio(lista2, contactos2[i], (FuncionCopia)contacto_copia);
    contacto_destruir(contactos2[i]);
  }
/*
  printf("Lista:\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  //a
  printf("%i\n",slist_longitud(lista));
  //b
  //glist_recorrer(slist_concatenar(lista,lista2), (FuncionVisitante)contacto_imprimir);
  printf("\n");
  //c
  glist_recorrer(slist_insertar(lista,3,contacto,(FuncionCopia)contacto_copia), (FuncionVisitante)contacto_imprimir);
  printf("\n");
  //d
  //slist_eliminar(lista,3,(FuncionDestructora)contacto_destruir);
  //glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  printf("\n");
  //e
  printf("%i\n",slist_contiene(lista,contacto,(FuncionComparadora)contacto_comparar));
  //f
  printf("%i\n",slist_indice(lista,contacto,(FuncionComparadora)contacto_comparar));
  //g,h
  printf("\n");
  GList lista3 = slist_intersecar_custom(lista2,lista2,(FuncionComparadora)contacto_comparar,(FuncionCopia)contacto_copia);
  glist_recorrer(lista3, (FuncionVisitante)contacto_imprimir);
  printf("\n");
  //i
  
  glist_recorrer(slist_ordenar(lista,(FuncionComparadora)contacto_comparar,(FuncionCopia)contacto_copia), (FuncionVisitante)contacto_imprimir);
  printf("\n");
  //j
  glist_recorrer(slist_reverso(lista,(FuncionCopia)contacto_copia), (FuncionVisitante)contacto_imprimir);
  printf("\n");
  //k
  glist_recorrer(slist_intercalar(lista,lista2,(FuncionCopia)contacto_copia), (FuncionVisitante)contacto_imprimir);
  //l
  printf("\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  printf("\n");
  glist_recorrer(slist_partir(lista), (FuncionVisitante)contacto_imprimir);
  printf("\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  printf("\n");
  */

  glist_recorrer(slist_partir_opt(lista), (FuncionVisitante)contacto_imprimir);
  printf("ES ESTA FLACO\n");
  printf("\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  glist_destruir(lista, (FuncionDestructora)contacto_destruir);
  glist_destruir(lista2, (FuncionDestructora)contacto_destruir);
  free(contacto);
  return 0;
}