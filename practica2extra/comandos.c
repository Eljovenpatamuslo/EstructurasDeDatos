#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _LineaIngresada{
    char* Comando;
    int* Argumentos;
    int cantArgumentos;
} LineaIngresada;

LineaIngresada asignar_lineaIngresada(char* input){
    LineaIngresada linea;
    int cantArgumentos = 0;
    char Comando[256];
    for(int i = 0; input[i] != '\n';i++){
        if(input[i] == ' '){
            
            cantArgumentos++;
        }
    }
}

char return_command(char* input){
    char command[256];
    int i = 0;
    for(; input[i] != ' ';i++){
        command[i] = input[i];
    }
    command[i] = '\0';
    return command;
}

char return_arguments(char* input){
    int amount = -1;
    
    for(int i = 0; input[i] != '\0';i++,amount++);
    return amount;
}



int main(){
    int input[256];
    printf("Ingrese algun comando: \n");
    scanf("%s",input);
    LineaIngresada linea = asignar_lineaIngresada(input);
}