#ifndef __SLIST_H__
#define __SLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _SNodo {
    void* dato;
    struct _SNodo *sig;
    struct _SNodo *ant;
} SNodo;

typedef struct SList {
    SNodo *primero;
    SNodo *ultimo;
} SList;


SList slist_crear();

SList slist_agregar_inicio(SList list, void* dato, FuncionCopia copy);

SList slist_agregar_final(SList list, void* dato, FuncionCopia copy);

void slist_destruir(SList list, FuncionDestructora destroy);

int slist_vacia(SList list);

SList slist_eliminar_ultimo(SList list,FuncionDestructora destroy);

void slist_imprimir(SList cola,FuncionVisitante visit);
#endif /* __SLIST_H__ */