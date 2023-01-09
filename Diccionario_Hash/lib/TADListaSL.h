#ifndef __TADLista_H
#define __TADLista_H
/*
IMPLEMENTACIONES DEL TAD LISTA (TADLista.h)
AUTOR: Edgardo Adrián Franco Martínez (C) Marzo 2017
VERSIÓN: 1.1

DESCRIPCIÓN: TAD lista o (list)
Estructura de datos en la que se cumple:
Los elementos se consultan, añaden y se remueven con base en posiciones
dentro de un arreglo lineal el cual cuenta con un frente o cabeza
y un final o cola.

OBSERVACIONES: Este archivo solo incluye las estructuras, tipos de datos y
declaración de las operaciones del TAD  Lista.

EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADListaSL.c
*/
#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

typedef struct elemento
{
	char p[101];
	char d[251];
} elemento;

// Estructura de un NODO SIMPLEMENTE LIGADO
typedef struct nodo
{
	elemento e;
	// Relación con el siguiente nodo
	struct nodo *siguiente;
	void *apellido;
} nodo;

// Se define una posicion como un apuntador a nodo
typedef nodo *posicion;

// Estructura de una lista
typedef struct lista
{
	int tam;
	posicion frente;
	posicion final;
	void *apellido;
} lista;

// Efecto: Recibe una lista l y la inicializa para su trabajo normal.
void Initialize(lista *l);

// Efecto: Recibe una lista l y la libera completamente
void Destroy(lista *l); // Maykaren Gomez Chávez, Alejandro Hernández Rodríguez.

// Efecto: Recibe una lista l y retorna la posición del elemento al final de esta.
posicion Final(lista *l); // Ramírez García Ana Rubí y Moreno Tinoco Aldo

// Efecto: Recibe una lista l y devuelve la posición del elemento al inicio de esta.
posicion First(lista *l); // Ramírez García Ana Rubí y Moreno Tinoco Aldo

// Efecto: Recibe una lista l, una posición p y devuelve la posición del elemento siguiente de p.
posicion Following(lista *l, posicion p); // Brandon GD

// Efecto: Recibe una lista l, una posición p y devuelve la posición del elemento anterior a p.
// Requerimientos: La lista l es no vacía y la posición p es una posición valida.
posicion Previous(lista *l, posicion p);

// Efecto: Recibe una lista l y un elemento e, devuelve la posición del elemento que coincida exactamente con e.
posicion Search(lista *l, elemento e);

// Efecto: Recibe una lista l, una posición p y devuelve el elemento en dicha posición.
// Requerimientos: La lista l es no vacía y la posición p es una posición valida.
elemento Position(lista *l, posicion p);

// Efecto: Recibe una lista l, una posición p y devuelve TRUE si la posición es una posición p valida en la lista l y FALSE en caso contrario.
boolean ValidatePosition(lista *l, posicion p);

// Efecto: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve la posición del elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
// Excepción: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se retorna una posición invalida.
posicion ElementPosition(lista *l, int n);

// Efecto: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve el elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
// Excepción: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se produce error.
elemento Element(lista *l, int n);

// Efecto: Recibe una lista l y devuelve el tamaño de la lista.
int Size(lista *l);

// Efecto: Recibe una lista l y devuelve TRUE en caso de que la lista este vacía y FALSE en caso contrario
boolean Empty(lista *l);

// Efecto: Recibe una lista l, una posición p, un elemento e y un valor booleano; el elemento e deberá agregarse al frente de p si b es verdadero y atrás de p en caso contrario.
// Requerimientos: La posición p es una posición valida, si p es no valida o NULL, se insertará a e al frente de la lista.
void Insert(lista *l, posicion p, elemento e, boolean b);

// Efecto: Recibe una lista l y un elemento e ; el elemento e deberá agregarse al final de la lista
void Add(lista *l, elemento e);

// Efecto: Recibe una lista l y una posición p, el elemento en la posición p será removido.
// Requerimientos: La lista l es no vacía y la posición p es una posición valida.
void Remove(lista *l, posicion p);

// Efecto: Recibe una lista l, una posición p y un elemento e, el elemento en la posición p será sustituido por e
// Requerimientos: La lista l es no vacía y la posición p es una posición valida.
void Replace(lista *l, posicion p, elemento e);

// Función para usarse en depuración, la cuál imprime las direcciones de
// memoria de los nodos y su apuntador a siguiente
void VerLigasLista(lista *l);
#endif // __TADLista_H
