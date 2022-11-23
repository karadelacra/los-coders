/*
main.c
V 1.0 Noviembre 2022
Autores:
    Darío Quiñones
    et al.

Evaluador de expresiones infijas en C. Toma una expresión escrita en notación
infija, la convierte a postfija y la evalúa. Toma la expresión como parámetro
en la forma:
> main.exe "expresion"

Por ejemplo:
> main.exe "2+3*4"
> main.exe "2+C*A/(B+5)"

Esta la convierte a una expresión postfija, la imprime y evalúa el resultado.
Se puede usar cualquiera de los operadores "+", "-", "*", "/", "^" y "()".
Y las incógnitas representadas por letras de la "A" a la "Z". Que al estar
presentes en la expresión, se les pedirá su valor al usuario.

Posteriormente imprime el resultado de la evaluación de la expresión.

Para compilar:
(Windows)
> gcc -o main.exe main.c pilas/pila-dinamica.c
(Linux)
> gcc -o main main.c pilas/pila-dinamica.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Dependiendo del tipo de pilas que se usen, se incluye una u otra librería
#include "pilas/pila-din.h"
// #include "pilas/pila-est.h"


bool parentesis_correctos(char *expresion);
bool mayor_precedencia(char a, char b);
char *reestructurar(char *expresion);
void consultar_incognitas(char *expresion, double *incognitas);
double evaluar(char *expresion, double *incognitas);


int main(int argc, char *argv[])
{
    char *expresion;
    double incognitas[26];

    // Recibir por argumento la expresión a evaluar
    if (argc != 2)
    {
        printf("\nIndique la expresion a evaluar - Ejemplo: \"%s (2+5)^2*3\"", argv[0]);
        exit(1);
    }

    expresion = argv[1];
    if (expresion == NULL)
    {
        printf("\nError al asignar la expresión %s", expresion);
		exit(1);
    }

    printf("\nExpresion: %s\n", expresion);
    if (parentesis_correctos(expresion))
    {
        printf("\nLos parentesis estan correctos");
        reestructurar(expresion);
        printf("\nExpresion reestructurada: %s", expresion);
        consultar_incognitas(expresion, incognitas);
        printf("\nResultado: %.4lf\n", evaluar(expresion, incognitas));
    }
    else
    {
        printf("\nLos parentesis no estan balanceados\n");
    }
}

/*
bool parentesis_correctos(char *expresion);
Recibe: *expresion: arreglo de caracteres a evaluar
Retorna:
    True si los parentesis estan balanceados y en el orden correcto,
    False en caso contrario.
*/
bool parentesis_correctos(char *expresion)
{
    pila s;
    bool balanceado = true;
    elemento e; // El valor de e no importa en este caso.
    int len, i = 0;

    Initialize(&s);
    len = strlen(expresion);
    for (i = 0; i < len; i++)
    {
        // Si se encuentra un parentesis de apertura, se agrega a la pila
        if (expresion[i] == '(')
        {
            Push(&s, e);
        }
        // Si se encuentra un parentesis de cierre, se saca de la pila
        else if (expresion[i] == ')')
        {
            if (Empty(&s))
            {
                balanceado = false;
                break;
            }
            else
            {
                Pop(&s);
            }
            Pop(&s);
        }
    }
    // Si la pila no está vacía, entonces no están balanceados
    if (!Empty(&s))
    {
        balanceado = false;
    }

    Destroy(&s);
    return balanceado;
}

/*
bool mayor_precedencia(char a, char b);
Recibe: a: caracter de un operador aritmético
        b: caracter de otro operador aritmético
Retorna: True si a > b
         False si a < b
Para simplificar las comparaciones entre operadores matemáticos.
*/
bool mayor_igual_precedencia(char a, char b){
    bool resultado;
    // Se le asigna un valor numérico a cada operador
    // de acuerdo a su precedencia
    int precedencia_a, precedencia_b;
    if (a != b) {
        switch (a)
        {
        case '^':
            precedencia_a = 3;
            break;
        case '*':
        case '/':
            precedencia_a = 2;
            break;
        case '+':
        case '-':
            precedencia_a = 1;
            break;
        default:
            precedencia_a = 0;
            break;
        }
        switch (b)
        {
        case '^':
            precedencia_b = 3;
            break;
        case '*':
        case '/':
            precedencia_b = 2;
            break;
        case '+':
        case '-':
            precedencia_b = 1;
            break;
        default:
            precedencia_b = 0;
            break;
        }
        resultado = precedencia_a > precedencia_b;
    }
    else{
        resultado = true;
    }
    return resultado;
}

/*
char *reestructurar(char *expresion);
Recibe: *expresion: arreglo de caracteres a modificar
Retorna: Un apuntador al un arreglo de caracteres modificado
*/
char *reestructurar(char *expresion){
    char *expresion_postfija;
    expresion_postfija = (char *)malloc(sizeof(char) * strlen(expresion));
    printf("\nExpresion: %s", expresion);
    return expresion_postfija;
}

/*
void consultar_incognitas(char *expresion, double *incognitas);
Recibe: *expresion: arreglo de caracteres a evaluar
        *incognitas: arreglo de doubles donde se guardarán los valores de las
        incógnitas.
Retorna: Un arreglo con los valores de las incognitas.
Escanea de la entrada estándar los valores de las incógnitas presentes en la
expresión.
*/
void consultar_incognitas(char *expresion, double *incognitas){
    printf("Expresion: %s\n", expresion);
    printf("Incognitas: %lf\n", incognitas[0]);
    return;
}

/*
double evaluar(char *expresion, double *incognitas);
Recibe: expresion a evaluar
        *incognitas: arreglo de doubles con los valores de las incógnitas.
Retorna: el resultado de evaluar la expresión recibida.
*/
double evaluar(char *expresion, double *incognitas){
    double resultado = 0;
    printf("Expresion: %s\n", expresion);
    printf("Incognitas: %lf\n", incognitas[0]);
    return resultado;
}