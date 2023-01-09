/*
IMPLEMENTACIONES DE LA LIBRERIA DEL TAD LISTA (TADLista.h)
AUTOR: Edgardo Adrián Franco Martínez (C)
VERSIÓN: 1.6 (Diciembre 2022)

DESCRIPCIÓN: TAD lista o (list)
Estructura de datos en la que se cumple:
Los elementos se consultan, añaden y se remueven con base en posiciones
dentro de un arreglo lineal el cual cuenta con un frente o cabeza
y un final o cola.

OBSERVACIONES: TADLista por definición es una Estructura de Datos dinámica.
La implementación del presente código se realiza mediante el principo de "Lista Simplemente Ligada"
i.e. nodos que contienen un elemento y se encuentran ligados hacia siguiente de estos.

Frente                                                       Final
	  ******    ******    ******    ******    ******    ******
	  *    *    *    *    *    *    *    *    *    *    *    *
	  * N1 *    * N2 *    * N3 *    * N4 *    * N5 *    * N6 *
	  *    * -> *    * -> *    * -> *    * -> *    * -> *    * -> NULL
	  ******    ******    ******    ******    ******    ******

COMPILACIÓN PARA GENERAR EL CÓDIGO OBJETO: gcc TADListaSL.c -c
*/

// LIBRERAS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TADListaSL.h"

// DEFINICIÓN DE FUNCIONES

/***************************************************
Operaciones de construcción
***************************************************/
/*
void Initialize(lista *l)
Descripción: Inicializar lista (Iniciar una lista para su uso)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve:
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Initialize(lista *l)
{
	l->frente = NULL;
	l->final = NULL;
	l->tam = 0;
	l->apellido = l;
	return;
}

/*
void Destroy(lista *l)
Descripción: Destruir una lista (Recibe una lista l y la libera completamente)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve:
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Destroy(lista *l)
{
	posicion aux;
	aux = l->frente;
	while (aux != NULL)
	{
		l->frente = aux->siguiente;
		free(aux);
		aux = l->frente;
	}
	l->final = NULL;
	l->tam = 0;
	return;
}

/***************************************************
Operaciones de posicionamiento y busqueda
***************************************************/
/*
posicion Final(lista *l)
Descripción: Recibe una lista l y regresa la posición del final (Recibe una
lista l y retorna la posición del elemento al final de esta.)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve: posición del nodo que contiene al elemeto final de la lista
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
posicion Final(lista *l)
{
	return l->final;
}

/*
posicion First(lista *l)
Descripción: Recibe una lista l y regresa la posición del frente (Recibe una
lista l y retorna la posición del elemento al frente de esta.)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve: posición del nodo que contiene al elemento del frente de la lista
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
posicion First(lista *l)
{
	return l->frente;
}

/*
posicion Following(lista *l, posicion p)
Descripción: Recibe una lista l, una posición p y devuelve la posición del
elemento siguiente de p
Recibe: lista *l y posicion p (Referencia a la lista "l" a operar y posición valida de la lista)
Devuelve: posición del nodo siguiente a la posicion dada
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, p es una posicion valida de la lista,
si esto no ha pasado se ocasionara un error.
*/
posicion Following(lista *l, posicion p)
{
	if (ValidatePosition(l, p))
		return p->siguiente;
	printf("ERROR:Following(L,p) la posicion es invalida");
	exit(1);
}

/*
posicion Previous(lista *l, posicion p)
Descripción: Recibe una lista L, una posición P y devuelve la posición del
elemento anterior de P
Recibe: lista *l y posicion p (Referencia a la lista "l" a operar y posición valida de la lista)
Devuelve: posición del nodo anterior a la posicion dada
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, p es una posicion valida de la lista, si esto no ha pasado se ocasionara un error.
*/
posicion Previous(lista *l, posicion p)
{
	posicion aux;
	aux = l->frente;
	// Si p es el frente
	if (p == l->frente)
		return NULL;
	while (!(aux == NULL || aux->siguiente == p))
		aux = aux->siguiente;

	if (aux == NULL)
	{
		printf("ERROR:Previous(L,p) posicion invalida");
		exit(1);
	}
	return aux;
}

/*
posicion Search(lista *l, elemento e)
Descripción: Recibe una lista l y un elemento e, regresa la posición que coincida exactamente con el elemento e.
Recibe: lista *l y un elemento e (Referencia a la lista "l" a operar y elemento a buscar en la lista)
Devuelve: posición del elemento en caso de ser encontrado, si no se encuentra se devuelve una posicion invalida
Observaciones: El usuario a creado una lista y l tiene la referencia a ella el elemento a buscar se compara directamente
a nivel de bytes.
*/
posicion Search(lista *l, elemento e)
{
	posicion aux = l->frente;
	while (aux != NULL)
	{
		if (memcmp(&aux->e, &e, sizeof(elemento)) == 0)
		{
			return aux;
		}
		aux = aux->siguiente;
	}
	return NULL;
}

/***************************************************
Operaciónes de consulta
/***************************************************/
/*
elemento Position(lista *l, posicion p)
Descripción: Recibe una lista l, una posición p y devuelve el elemento en dicha posición.
Recibe: lista *l y una posicion p(Referencia a la lista "l" a operar posicion valida en la lista)
Devuelve: Elemento en la posicion dada, si la posicion es invalida se genera error.
Observaciones: La lista l es no vacía y la posición p es una posición valida.
*/
elemento Position(lista *l, posicion p)
{
	if (ValidatePosition(l, p))
		return p->e;
	printf("ERROR:Position(L,p) la posicion es invalida");
	exit(1);
}

/*
boolean ValidatePosition(lista *l, posicion p)
Descripción: Recibe una lista l, una posición p y devuelve TRUE si la posición es una posición p valida en la lista l y FALSE en caso contrario.
Recibe: lista *l y una posicion p(Referencia a la lista "l" a operar y una posicion)
Devuelve: Booleano
Observaciones:
*/
boolean ValidatePosition(lista *l, posicion p)
{
	boolean b = FALSE;
	if (p != NULL)
		if (p->apellido == l->apellido)
			b = TRUE;
	return b;
}

/*
elemento Element(lista *l, int n)
Descripción: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve el elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
Recibe: lista *l y una entero
Devuelve: elemento
Observaciones: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se produce error.
*/
elemento Element(lista *l, int n)
{
	int i = 1;
	posicion aux = l->frente;
	if (n > 0 && n <= l->tam)
	{
		while (i < n)
		{
			i++;
			aux = aux->siguiente;
		}
		return aux->e;
	}
	printf("ERROR:Element(L,n)n invalido");
	exit(1);
	/*
	posicion aux=ElementPosition(l,n);
	return Element(l,aux);
	*/
}

/*
posicion ElementPosition(lista *l, int n)
Descripción: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve la posicion del elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
Recibe: lista *l y una entero
Devuelve: posicion
Observaciones: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se produce error.
*/
posicion ElementPosition(lista *l, int n)
{
	int i = 1;

	posicion aux = l->frente;
	if (n > 0 && n <= l->tam)
	{
		while (i < n)
		{
			i++;
			aux = aux->siguiente;
		}
		return aux;
	}
	printf("ERROR: ElementPosition(L,n)n invalido");
	exit(1);
}

/*
int Size(lista * l);
Descripción: Recibe una lista y devuelve el número de elemento que se encuentran en esta.
Recibe: lista *l (Referencia a la lista "l")
Devuelve: int (Tamaño de la lista)
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
int Size(lista *l)
{
	return l->tam;
}

/*
int Size(lista * l);
Descripción: Recibe una lista l y devuelve TRUE en caso de que la lista este vacía y FALSE en caso contrario.
Recibe: lista *l (Referencia a la lista "l")
Devuelve: boolean (TRUE o FALSE)
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
boolean Empty(lista *l)
{
	boolean r;
	if (l->tam == 0)
		r = TRUE;
	else
		r = FALSE;
	return r;
}
/***************************************************
Operaciones de modificación
****************************************************/
/*
void Insert (lista * l, posicion p, elemento e, boolean b);
Descripción: Inserta un elemento e en la lista este deberá agregarse al frente de p
si b es verdadero y atrás de p en caso contrario. Si p es invalida
Recibe: lista *l (Referencia a la lista "l"), posición p (Posición valida o invalida en la lista),
elemento e (Elemento a insertar en la lita), boolean b (Indicador de inserción antes de p=TRUE o despues de p =FALSE)
Devuelve:
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, si P es no valida o NULL,
se insertará a e al frente de la lista.
*/
void Insert(lista *l, posicion p, elemento e, boolean b)
{
	posicion aux, aux2;
	aux = malloc(sizeof(nodo));
	if (aux == NULL)
	{
		printf("ERROR: Insert (l,p,e,b) Desbordamiento de lista.");
		exit(1);
	}
	aux->e = e;
	aux->apellido = l->apellido;
	if (ValidatePosition(l, p))
	{
		if (b) // Enfrente de p
		{
			aux2 = Previous(l, p);
			if (aux2 == NULL) // p es el frente, se inserta al frente de la lista
			{
				aux->siguiente = l->frente;
				l->frente = aux;
				l->tam++;
			}
			else // Si p no era el frente de la lista
			{
				aux2->siguiente = aux;
				aux->siguiente = p;
				l->tam++;
			}
		}
		else // Atras de p
		{
			aux2 = Following(l, p);
			if (aux2 == NULL) // p es el final, se inserta al final de la lista
			{
				p->siguiente = aux;
				l->final = aux;
				aux->siguiente = NULL;
				l->tam++;
			}
			else // Si p no era el frente de la lista
			{
				p->siguiente = aux;
				aux->siguiente = aux2;
				l->tam++;
			}
		}
	}
	else // si p es invalido, se inserta e enfrente
	{
		aux->siguiente = l->frente;
		l->frente = aux;
		if (l->tam == 0)
			l->final = aux;
		l->tam++;
	}
	return;
}

/*
void Add (lista *l,elemento e);
Descripción: Recibe una lista l y un elemento e, se agrega a e al final de la lista l.
Recibe: lista *l (Referencia a la lista "l"), elemento e (Elemento a insertar en la lita)
Devuelve:
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
void Add(lista *l, elemento e)
{
	posicion aux;
	aux = malloc(sizeof(nodo));
	if (aux == NULL)
	{
		printf("ERROR: Add (l,e) desbordamiento de lista");
		exit(1);
	}
	aux->e = e;
	aux->apellido = l->apellido;
	if (l->tam > 0)
		l->final->siguiente = aux;
	else
		l->frente = aux;
	l->final = aux;
	l->tam++;
	return;
}

/*
void Remove (lista *l,posicion p);
Descripción: Recibe una lista l y una posición p, el elemento en la posición p será removido.
Recibe: lista *l (Referencia a la lista "l"), posicion p (posicion a eliminar en la lista)
Devuelve:
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, la posicion p es valida.
*/
void Remove(lista *l, posicion p)
{
	posicion aux;
	if (!ValidatePosition(l, p))
	{
		printf("ERROR: Remove (l,p), p es invalida");
		exit(1);
	}
	if (p == l->frente)
	{
		l->frente = p->siguiente;
	}
	else if (p == l->final)
	{
		aux = Previous(l, p);
		aux->siguiente = NULL;
		l->final = aux;
	}
	else
	{
		aux = Previous(l, p);
		aux->siguiente = p->siguiente;
	}
	free(p);
	l->tam--;
	if (l->tam == 0)
		l->final = NULL;
	return;
}

/*
void Replace (lista *l,posicion p, elemento e);
Descripción: Recibe una lista l, una posición p y un elemento e, el elemento en la posición p será sustituido por e
Recibe: lista *l (Referencia a la lista "l"), posicion p (posicion a remplazar en la lista), elemento e (elemento que remplazara al existente en p)
Devuelve:
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, la posicion p es valida.
*/
void Replace(lista *l, posicion p, elemento e)
{
	if (ValidatePosition(l, p))
	{
		p->e = e;
	}
	else
	{
		printf("ERROR: Replace(l,p,e) Posición invalida");
		exit(1);
	}
	return;
}

/********************************************************************************
//Función para usarse en depuración, la cuál imprime las direcciones de
//memoria de los nodos y su apuntador a siguiente
********************************************************************************/
void VerLigasLista(lista *l)
{
	posicion aux;
	aux = l->frente;
	printf("\n*************************************************************");
	while (aux != NULL)
	{
		printf("\nPosicion=%d\tSiguiente=%d", aux, aux->siguiente);
		aux = aux->siguiente;
	}
	printf("\n*************************************************************");

	return;
}
