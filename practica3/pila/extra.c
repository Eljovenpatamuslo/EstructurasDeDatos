#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int operacion_a_valor(char* str){
    Pila* pila = pila_crear();
    int valor = 0;
    for(int i = 0; str[i] != '\0'; i++){

        if(str[i] == ')' || str[i-1] == '*' || str[i-1] == '/'){
            char num2 = pila.pop();
            char operador = pila.pop();
            char num1 = pila.pop();
            if(str[i] == ')') pila.pop();
            pila.push(calcular_valor(num1,operador,num2));
        }   
    }
}

int calcular_valor(char num1, char operador, char num2){
    int valor1 = num1 - 48;
    int valor2 = num2 - 48;

    if(operador == "+") return valor1 + valor2;
    if(operador == "-") return valor1 - valor2;
    if(operador == "*") return valor1 * valor2;
    return valor1 / valor2;
}


dos pilas
una operadores otros operandos
ignorar (
cuando tenes un ) resolvemos (operacion binaria) y almacenamos el valor en los operandos

cuando la pila del operador sea vacia, entonces devolvemos el ultimo valor de la pila de operandos (esto porque cuando ponemos * no solemos poner parentesis )

*/

int eval_l(char *expr)
    Pila operandos = pila_crear();
    Pila operadores =  
int main(){
    calcular_valor("(1+(1+2)*4*5)");
}

