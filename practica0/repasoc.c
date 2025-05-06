#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
1. Escriba un programa que declare algunas variables locales, e imprima las direcciones de memoria de
las mismas. Pruebe declarar un arreglo de caracteres, y verifique que las direcciones de sus elementos
son contiguas.
*/
void fun1(){
    int a;
    char b;
    char c[] = {'a','b','c'};

    printf("%p\n",&a);
    printf("%p\n",&b);
    printf("%p\n",&c);

    printf("%c, %p\n",c[0] ,&c[0]);
    printf("%c, %p\n",c[1] ,&c[1]);
    printf("%c, %p\n",c[2] ,&c[2]);
    
}

/*
2. Implemente una funci ́on void set_first(int []) que ponga en cero el primer elemento del arreglo
recibido. Verifique desde la funci ́on llamante que efectivamente modifica este valor. ¿Por qu ́e pasa esto?
¿No llama a la funcion por valor?
*/
void set_first(int a[]){
    a[0] = 0;
}

/*
3. Implemente una funcion set_in(int *) que toma un puntero a un entero, y reemplaza el entero
apuntado por un 1 si el entero apuntado era diferente a 0, y 0 en caso contrario
*/

void set_in(int *a){
    if(*a != 0){
        *a = 1;
    }else{
        *a = 0;
    }
}

/*
4. Implemente una funci ́on void swap(int *, int *) que dados dos punteros a variables, intercambie
el contenido de las variables apuntadas.
*/

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/*
5. Explique el tipo de la funci ́on malloc de stdlib.h, ¿qu ́e valor retorna la funci ́on en caso de que no
pueda reservar el espacio solicitado?
*/
//la funcion malloc devuelve un puntero del temaño pedido, si no hay mas memoria disponible devuelve null

/*
6. Implemente una funci ́on char *get new line(void) que ingrese una linea por teclado (hasta \n), y
devuelva un puntero a la cadena ingresada.
*/

char* get_new_line(){
    char buffer[256];
    scanf("%[^\n]",buffer);
    char* linea = malloc(sizeof(char)*strlen(buffer));
    strcpy(linea,buffer);
    return linea;
}

/*
7. Escriba un programa que reserve un espacio de memoria de 100 bytes, y luego lib ́erelo dos veces. ¿Se
produce alg ́un error?
*/

void fun7(){
    void *a = malloc(100);
    free(a);
    free(a);
}

/*
8. Implemente las siguientes funciones que reciben como argumento punteros a funcion:
*/

/*
a) int apply(int (*)(int), int) que toma un puntero a funci ́on, y un entero, y aplica la funci ́on al
entero y retorna el valor dado.
*/
int apply(int(*f)(int),int a){
    return f(a);
}

/*
b) void apply in(int (*)(int), int*) que toma un puntero a funci ́on, un puntero a un entero, y
reemplaza el entero apuntado por el valor de ejecutar la funci ́on apuntada sobre el valor apuntado.
*/

void apply_in(int(*f)(int),int *a){
    *a = f(*a);
}

/*
c) void recorre(VisitorFunc, int[], int) que toma un puntero a una funci ́on, un arreglo de enteros,
y su longitud, y aplica la funci ́on a cada elemento del arreglo. VisitorFunc est ́a definido por
typedef void (*VisitorFunc)(int).
*/
typedef void (*VisitorFunc)(int);
void recorre(VisitorFunc a,int b[], int c){
    for(int i = 0; i < c; i++){
        a(b[i]);
    }
}

/*
d) Pruebe las funciones anteriores pas ́andoles como parametro las siguientes funciones:
*/

//i. Para a y b:
int sucesor (int n) {
    return n+1;
}
//ii. Para c:
void imprimir (int n) {
    printf("%d \n", n);
}


int main(){
    //1
    printf("ejer 1\n");
    fun1();
//-----------
    //2
    printf("ejer 2\n");
    {
        int a[] = {1,2,3,4};
        printf("%i\n",a[0]);
        set_first(a);
        printf("%i\n",a[0]);
    }
//--------------
    //3
    printf("ejer 3\n");

    {
        int *a = malloc(sizeof(int)*3);
        a[0] = 4;
        a[1] = 0;
        a[2] = 1;

        set_in(a);
        printf("%i\n",*a);
        a++;
        set_in(a);
        printf("%i\n",*a);
    }

//--------------
    //4
    printf("ejer 4\n");

    {
        int *a = malloc(sizeof(int)*3);
        int *b = malloc(sizeof(int)*3);

        a[0] = 3;
        b[0] = 7;
        printf("a:%i\n",*a);
        printf("b:%i\n",*b);
        swap(a,b);
        printf("a:%i\n",*a);
        printf("b:%i\n",*b);
    }
//--------------
    //6
    printf("ejer 6\n");

    {
        char* linea = get_new_line();
        printf("%s\n",linea);
    }
//--------------
    //7
    printf("ejer 7\n");
    {
        fun7();
    }

//--------------
    //8
    printf("ejer 8\n");
    {
        printf("a)\n");
        printf("%i\n",apply(sucesor,3));
        printf("b)\n");
        int *a = malloc(sizeof(int) * 3);
        a[0] = 4; 
        apply_in(sucesor,a);
        printf("%i\n",a[0]);
        printf("c)\n");
        int b[] = {1,2,3,4};
        recorre(imprimir,b,4);

    }
    return 0;
}