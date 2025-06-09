#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _persona {
    int grupo;
    char nombre[256];
    int pos;

}Persona;


int compa(const void* dato1, const void* dato2){
    Persona persona1 = *((Persona*)dato1);
    Persona persona2 = *((Persona*)dato2);
    
    if(persona1.grupo != persona2.grupo) return persona1.grupo - persona2.grupo;
    return persona1.pos - persona2.pos;
}

int main(){
    Persona *persona = malloc(sizeof(Persona)*4);
    persona[0].grupo = 1;
    strcpy(persona[0].nombre,"Pata");
    persona[0].pos = 0;
    persona[2].grupo = 1;
    strcpy(persona[2].nombre,"Jaffre");
    persona[2].pos = 2;
    persona[1].grupo = 2;
    strcpy(persona[1].nombre,"Conga");
    persona[1].pos = 1;
    persona[3].grupo = 2;
    strcpy(persona[3].nombre,"Ayrton");
    persona[3].pos = 3;
    qsort(persona,4,sizeof(Persona),compa);
    for(int i=0 ;i <4;i++){
        printf("Grupo %i, nombre:%s\n",persona[i].grupo,persona[i].nombre);
    }
    return 0;
}