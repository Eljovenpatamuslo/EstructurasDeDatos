#ifndef __SLIST_H__
#define __SLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _SNodo {
    void* dato;
    struct _SNodo *sig;
} SNodo;

typedef struct SList {
    SNodo *primero;
    SNodo *ultimo;
} SList;


SList slist_crear();

SList slist_agregar_inicio(SList list, void* dato, FuncionCopia copy);

SList slist_agregar_final(SList list, void* dato, FuncionCopia copy);

#endif /* __SLIST_H__ */