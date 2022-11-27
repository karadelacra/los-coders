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
#include <string.h> // Para usar strlen()
#include <stdbool.h> // Para usar bool estándar
#include <math.h> // Para usar pow() y valores NaN

// Dependiendo del tipo de pilas que se usen, se incluye una u otra librería
#include "pilas/pila-din.h"
// #include "pilas/pila-est.h"


bool parentesis_correctos(char *expresion);
bool mayor_igual_precedencia(char a, char b);
void reestructurar(char *expresion, char *expresion_postfija);
void consultar_incognitas(char *expresion, double *incognitas);
double evaluar(char *expresion, double *incognitas);


int main(int argc, char *argv[])
{
    char *expresion, *expresion_postfija;
    double incognitas[26];

    // Recibir por argumento la expresión a evaluar
    if (argc != 2)
    {
        printf("\nIndique la expresion a evaluar \n\tEjemplo: \'%s \"(2+5)^2*3\"\'\n", argv[0]);
        exit(1);
    }

    expresion = argv[1];
    if (expresion == NULL)
    {
        printf("\nError al asignar la expresión");
		exit(1);
    }

    printf("\nExpresion: %s\n", expresion);
    if (parentesis_correctos(expresion))
    {
        printf("Los parentesis estan correctos\n");

        // Reestructurar la expresión
        expresion_postfija = (char *) malloc((int)(strlen(expresion) * sizeof(char) * 1.5));
        reestructurar(expresion, expresion_postfija);
        printf("Expresion reestructurada: %s\n", expresion_postfija);

        consultar_incognitas(expresion, incognitas);
        printf("\nResultado: %.4lf\n", evaluar(expresion_postfija, incognitas));
    }
    else
    {
        printf("Los parentesis no estan correctos\n");
        exit(1);
    }

    return 0;
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
Retorna: True si a >= b 
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
            //potencia máxima prioridad
        case '^':
            precedencia_a = 3;
            break;
            //mult y división prioridad media
        case '*':
        case '/':
            precedencia_a = 2;
            break;
            //suma y resta prioridad baja
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
        resultado = precedencia_a >= precedencia_b;
    }
    else{
        resultado = true;
    }
    return resultado;
}

/*
void *reestructurar(char *expresion, char *expresion_postfija);
Recibe: *expresion: arreglo de caracteres a modificar
        *expresion_postfija: arreglo de caracteres donde se guardará la expresión postfija
Retorna: Un apuntador al un arreglo de caracteres modificado
*/
void reestructurar(char *expresion, char *expresion_postfija){
    pila s;
    elemento e;
    int len, i = 0, j = 0;

    Initialize(&s);
    len = strlen(expresion);
    //Definimos una expresión por defecto vacía para la expresión postfija
    expresion_postfija[0]='\0';
    for (i = 0; i < len; i++)
    {
        // Si es un número, se agrega a la expresión postfija
        if (expresion[i] >= '0' && expresion[i] <= '9')
        {
            // Si el valor anterior era un número, se agrega un espacio
            if (j > 0 && expresion_postfija[j-1] >= '0' && expresion_postfija[j-1] <= '9')
            {
                expresion_postfija[j] = ' ';
                j++;
            }
            expresion_postfija[j] = expresion[i];
            j++;
            // Mientras haya un valor siguiente, y ese sea parte del número
            while (i+1 < len && ((expresion[i+1] >= '0' && expresion[i+1] <= '9') || expresion[i+1] == '.'))
            {
                i++;
                // Se agrega el siguiente valor a la expresión postfija
                expresion_postfija[j] = expresion[i];
                j++;
            }
        }
        // Si es una incógnita, se agrega a la expresión postfija
        else if (expresion[i] >= 'A' && expresion[i] <= 'Z')
        {
            expresion_postfija[j] = expresion[i];
            j++;
        }
        // Si es un operador, se agrega a la pila
        else if (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/' || expresion[i] == '^')
        {
            // Si la pila está vacía, se agrega el operador a la misma.
            if (Empty(&s))
            {
                e.dato = expresion[i];
                Push(&s, e);
            }
            // Si la pila no está vacía, se compara la precedencia del operador
            // con el operador en la cima de la pila
            else
            {
                // Si el operador en la cima de la pila tiene mayor o igual
                // precedencia se agrega a la expresión postfija
                while (!Empty(&s) && mayor_igual_precedencia(Top(&s).dato, expresion[i]))
                {
                    expresion_postfija[j] = Pop(&s).dato;
                    j++;
                }
                // Si el operador en la cima de la pila tiene menor precedencia
                // se agrega a la pila
                e.dato = expresion[i];
                Push(&s, e);
            }
        }
        // Si es un parentesis de apertura, se agrega a la pila
        else if (expresion[i] == '(')
        {
            e.dato = expresion[i];
            Push(&s, e);
        }
        // Si es un parentesis de cierre, se sacan los operadores de la pila
        // hasta encontrar un parentesis de apertura
        else if (expresion[i] == ')')
        {
            while (Top(&s).dato != '(')
            {
                expresion_postfija[j] = Top(&s).dato;
                j++;
                Pop(&s);
            }
            Pop(&s);
        }
        // // Imprime la cima de la pila
        // if (!Empty(&s))
        //     printf("Cima de la pila: %c\n", Top(&s).dato);
        // else
        //     printf("Cima de la pila: NULL\n");
    }

    // Se sacan los operadores de la pila
    while (!Empty(&s))
    {
        expresion_postfija[j] = Pop(&s).dato;
        j++;
    }
    j++;
    expresion_postfija[j] = '\0';
    Destroy(&s);
    return;
}

/*
void consultar_incognitas(char *expresion, double *incognitas);
Recibe: *expresion: arreglo de caracteres a evaluar
        *incognitas: arreglo de doubles donde se guardarán los valores de las
        incógnitas.
Retorna: Un arreglo con los valores de las incognitas.
Escanea de la entrada estándar los valores de las incógnitas presentes en la
expresión en orden alfabético.
*/
void consultar_incognitas(char *expresion, double *incognitas){
    int i, len;
    for (i = 0; i < 26; i++)
    {
        // Para cada incognita, se le asigna un valor que no es un número
        incognitas[i] = 0.0/0.0;
    }

    len = strlen(expresion);
    for (i = 0; i < len; i++)
    {
        // Si el caracter es una letra, y esa letra no ha sido asignada
        // un valor, se le pide al usuario que ingrese un valor
        if (expresion[i] >= 'A' && expresion[i] <= 'Z' && isnan(incognitas[expresion[i] - 'A'])){
            {
                printf("Valor de %c: ", expresion[i]);
                scanf("%lf", &incognitas[expresion[i] - 'A']);
                if (isnan(incognitas[expresion[i] - 'A']))
                {
                    printf("Valor no válido\n");
                    exit(1);
                }
            }
        }
    }
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
    pila s;
    elemento e;
    int i,j=0,len;
    char *buffer, *ptr;
    double valor1, valor2;
    double operaciones;

    len = strlen(expresion);

    Initialize(&s);
    for (i=0;i<len;i++)
    {
        // Si es un número se agregan al buffer todos sus caracteres.
        if (expresion[i] >= '0' && expresion[i] <= '9')
        {
            buffer = (char *)malloc(101*sizeof(char));
            buffer[j] = expresion[i];
            j++;
            // Mientras haya un valor siguiente, y ese sea parte del número
            while (i+1 < len && ((expresion[i+1] >= '0' && expresion[i+1] <= '9') || expresion[i+1] == '.'))
            {
                i++;
                // Se agrega el siguiente valor a la expresión postfija
                buffer[j] = expresion[i];
                j++;
            }
            buffer[j]='\0';
            printf("buffer = %s\n",buffer);
            j=0;
            e.dato=buffer;
            Push(&s,e);
        }
        // Si es una incógnita, procedemos a sustituir el valor con lo guardado en el arreglo de incógnitas
        else if (expresion[i] >= 'A' && expresion[i] <= 'Z')
        {
            buffer = (char *)malloc(101*sizeof(char));
            sprintf(buffer,"%lf",incognitas[expresion[i]-'A']);
            e.dato = buffer;
            Push(&s,e);
        }

        // Si es un operador, procede a realizarse la operación.
        else if (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/' || expresion[i] == '^')
        {
            // Si la pila no está vacía, realizamos la operación con los dos últimos valores.
            if (!Empty(&s))
            {
                ptr = (Pop(&s).dato);
                valor1=atof(ptr);
                free(ptr);
            }
            if (!Empty(&s))
            {
                ptr = (Pop(&s).dato);
                valor2=atof(ptr);
                free(ptr);
            }
            switch (expresion[i])
            {
                //potencia máxima prioridad
                case '^':
                    operaciones = pow(valor2,valor1);
                    break;
                //mult y división prioridad media
                case '*':
                    operaciones = valor2*valor1;
                    break;
                case '/':
                    operaciones = valor2/valor1;
                    break;
                //suma y resta prioridad baja
                case '+':
                    operaciones = valor2 + valor1;
                    break;
                case '-':
                    operaciones = valor2 - valor1;
                    break;
                default:
                    break;
            }
            buffer = (char *)malloc(101*sizeof(char));
            sprintf(buffer,"%lf",operaciones);
            printf("buffer = %s\n",buffer);
            e.dato=buffer;
            Push(&s,e);
        }
    }
    if(!Empty(&s))
    {
        ptr=Pop(&s).dato;
        resultado=atof(ptr);
        free(ptr);
    }
    Destroy(&s);
    return resultado;
}