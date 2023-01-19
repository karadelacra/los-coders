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
//#include "../TAD_Lista/TADListaSL.h"

typedef struct elemento
{
	char p[101];
	char d[251];
} elemento;

typedef struct nodoBin
{
    elemento dato;
    // Relación con el siguiente nodo
    struct nodoBin *izq;
    struct nodoBin *der;
    struct nodoBin *padre;
    //int clave;
    //int peso;
    void *apellido;
} nodoBin;

// Se define una posicion como un apuntador a nodo
typedef nodoBin *posicion;

// Estructura de un ABB
typedef struct abb
{
    int nivel, tam;
    int ultbusq;
    posicion raiz;
    posicion finabb;
    void *apellido;
} abb;


//OPERACIONES DE CONSTRUCCI�N
void Initialize (abb *a);									// Efecto: Recibe un ABB a y lo inicializa para su trabajo normal.
void Destroy (abb *a);										// Efecto: Recibe un ABB a y lo libera completamente.
//OPERACIONES DE POSICIONAMIENTO Y B�SQUEDA
posicion Root(abb *a);										// Efecto: Recibe un ABB y devuelve la posici�n de la ra�z.
posicion Parent(abb *a, posicion p);						// Efecto: Recibe un ABB a y una posici�n p, devuelve la posici�n de el padre.
posicion RightSon(abb *a, posicion p);						// Efecto: Recibe un ABB a y una posici�n p, devuelve la posici�n del hijo derecho.
posicion LeftSon(abb *a, posicion p);						// Efecto: Recibe un ABB a y una posici�n p, devuelve la posici�n del hijo izquierdo.
posicion Search(abb *a, elemento e);						// Efecto: Recibe un ABB a y un elemento e, devuelve la posici�n del elemento en el �rbol.
posicion BuscarPosPalabra(posicion nodo, char palabra[101]);// Efecto: Recibe una posicion nodo y una palabra[101] y busca recursivamente si la palabra se encuentra en el �rbol
//OPERACIONES DE CONSULTA
bool Empty (abb *a);										// Efecto: Recibe un ABB a y devuelve si la lista est� vac�a.
bool NullNode(abb *a, posicion p);							// Efecto: Recibe un ABB a y una posici�n p, devuelve verdadero si la posici�n p del ABB es nula o incorrecta.
bool BuscarPosicion(posicion nodo, posicion p); 			// Efecto: Recibe una posicion nodo y una posicion p y busca recursivamente si la posicion p se encuentra en el �rbol
int Size (abb *a);											// Efecto: Recibe un ABB a y regresa el tamaño de la lista.
elemento Element(abb *a, posicion p);						// Efecto: Recibe un ABB y una posici�n p, regresa el elemento en dicha posici�n.
void RecorridoPreOrden(nodoBin *nodo);						// Efecto: Recibe una posici�n e imprime el PreOrden de los elementos del �rbol a partir de la posici�n dada.
void RecorridoInOrden(nodoBin *nodo);						// Efecto: Recibe una posici�n e imprime el InOrden de los elementos del �rbol a partir de la posici�n dada.
void RecorridoPosOrden(nodoBin *nodo);						// Efecto: Recibe una posici�n e imprime el PostOrden de los elementos del �rbol a partir de la posici�n dada.
int altura(nodoBin *nodo);
//OPERACIONES DE MODIFICACI�N
void Add(abb *a, elemento e);								// Efecto: Recibe un ABB a y un elemento e, el elemento e se agregar� al �rbol dependiendo de su tama�o
void ReplaceDefinition(abb *a, posicion p, char def[251]);	// Efecto: Recibe un ABB a, una posici�n p y una definici�n, reemplaza la definici�n del elemento en la posici�n dada.
void Remove(abb *a, posicion p);
//OPERACIONES DE CONSULTA (DEPURACI�N)
void VerLigas(abb *a);										// Efecto: Imprime c�mo est� enlazado el �rbol binario a detalle.
void PreOrdenDetallado(nodoBin *nodo);						// Efecto: Recibe una posici�n e imprime el PreOrden de los elementos del �rbol a partir de la posici�n dada.
void InOrdenDetallado(nodoBin *nodo);						// Efecto: Recibe una posici�n e imprime el InOrden de los elementos del �rbol a partir de la posici�n dada.
void PosOrdenDetallado(nodoBin *nodo);						// Efecto: Recibe una posici�n e imprime el PostOrden de los elementos del �rbol a partir de la posici�n dada.
void Detalles(nodoBin *nodo);								// Efecto: Imprime los detalles de un elemento del �rbol.










// Efecto: Recibe un ABB a y devuelve si la posición es válida.
bool ValidPositionabb(abb *a, posicion p);

// Efecto: recibe un ABB a y un indice entre 1 y el tamaño de la lista y devuelve el elemento en la posición indice.
posicion Positionabb(abb *a, int indice);










// Efecto: Recibe un ABB y una posición p, el elemento en la posición p será removido.
// Requerimientos: El ABB es no vacío y la posición p es una posición valida.
void Removeabb(abb *a, posicion p);

// Efecto: Recibe la posición de un hijo, compara el valor con su padre y si es menor lo intercambia de lugar.
void Swap(abb *a, posicion p);

//

#endif // __TADABB_H
