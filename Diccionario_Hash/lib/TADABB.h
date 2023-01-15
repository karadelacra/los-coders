#ifndef __TADABB_H
#define __TADABB_H
/*
IMPLEMENTACIONES DEL TAD ABB (TADABB.h)
AUTOR: Padilla Escobar Karel Roman (C) Marzo 2017
VERSIÓN: 1.0

DESCRIPCIÓN: TAD ABB (Árbol Binario de Búsqueda)
Estructura de datos en la que se cumple:
Los elementos se consultan, añaden y se remueven con base en posiciones
dentro de un arreglo de arbol binario de busqueda.
el cual cuenta con un no do que tiene hijos izquierdo y derecho.
cada hijo es mayor que el padre y si el padre es mayor que el hijo, se intercambian de lugar.

Observaciones: Este archivo solo incluye las estructuras, tipos de datos y
declaración de las operaciones del TAD  ABB.
*/
#include <stdbool.h>
#include "TADListaSL.h"

typedef struct nodoBin
{
    elemento dato;
    // Relación con el siguiente nodo
    struct nodoBin *izq;
    struct nodoBin *der;
} nodoBin;

// Se define una posicion como un apuntador a nodo
typedef nodoBin *posicionBin;

// Estructura de un ABB
typedef struct abb
{
    int nivel, tam;
    posicionBin raiz;
    posicionBin finabb;
    void *apellido;
} abb;

// Efecto: Recibe un ABB a y lo inicializa para su trabajo normal.
void Initializeabb(abb *a);

// Efecto: Recibe un ABB a y retorna la posición del elemento al final agregado.
posicionBin Finalabb(abb *a);

// Efecto: Recibe un ABB a y devuelve la posición del elemento a la cabeza.
posicionBin Firstabb(abb *a);

// Efecto: Recibe un ABB a y devuelve la posición de el padre.
posicionBin Parent(abb *a, posicionBin p);

// Efecto: Recibe un ABB a y devuelve la posición del hijo izquierdo.
posicionBin LeftChild(abb *a, posicionBin p);

// Efecto: Recibe un ABB a y devuelve la posición del hijo derecho.
posicionBin RightChild(abb *a, posicionBin p);

// Efecto: Recibe un ABB a y devuelve la posición del elemento que coincida con la palabra.
posicionBin Find(abb *a, char *palabra);

// Efecto: Recibe un ABB a y devuelve la definición de la palabra.
posicionBin Definition(abb *a, char *palabra);

// Efecto: Recibe un ABB a y devuelve si la posición es válida.
boolean ValidPositionabb(abb *a, posicionBin p);

// Efecto: recibe un ABB a y un indice entre 1 y el tamaño de la lista y devuelve el elemento en la posición indice.
posicionBin Positionabb(abb *a, int indice);

// Efecto: Recibe una ABB a y regresa el tamaño de la lista.
int Sizeabb(abb *a);

// Efecto: Recibe un ABB a y devuelve si la lista está vacía.
boolean Emptyabb(abb *a);

// Efecto: Recibe una lista l y un elemento e ; el elemento e deberá agregarse al final de la lista
void Addabb(abb *a, char *palabra, char *definicion);

// Efecto: Recibe un ABB y una posición p, el elemento en la posición p será removido.
// Requerimientos: El ABB es no vacío y la posición p es una posición valida.
void Removeabb(abb *a, posicionBin p);

// Efecto: Recibe la posición de un hijo, compara el valor con su padre y si es menor lo intercambia de lugar.
void Swap(abb *a, posicionBin p);

//

#endif // __TADABB_H