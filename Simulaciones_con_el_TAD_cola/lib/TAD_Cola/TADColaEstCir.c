/*
IMPLEMENTACION DE LA LIBRERIA DEL TAD COLA ESTATICA (TADColaEst.h)
AUTOR: Edgardo Adrián Franco Martínez (C) Noviembre 2022
VERSIÓN: 1.7

DESCRIPCIÓN: TAD cola o Queue.
Estructura de datos en la que se cumple:
Los elementos se insertan en un extremo (el posterior) y
la supresiones tienen lugar en el otro extremo (frente).

OBSERVACIONES: Hablamos de una Estructura de datos estática cuando
se le asigna una cantidad fija de memoria para esa estructura
antes de la ejecución del programa.

COMPILACIÓN PARA GENERAR EL CÓDIGO OBJETO: gcc -c TADColaEst.c
*/

//LIBRERAS
#include "TADColaEst.h"
#include <stdlib.h>
#include <stdio.h>
//DEFINICIÓN DE FUNCIONES

/*
void Initialize(cola *c);
Descripción: Inicializar cola (Iniciar una cola para su uso)
Recibe: cola *c (Referencia a la cola "c" a operar)
Devuelve:
Observaciones: El usuario a creado una cola y c tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Initialize(cola * c)
{
	c->frente=-1;
	c->final=-1;
	c->num_elem=0;
	return;
}

/*
void Queue(cola * c, elemento e);
Descripción: Recibe una cola y agrega un elemento al final de ella.
Recibe: cola *c (Referencia a la cola "c" a operar) elemento e (Elemento a encolar)
Devuelve:
Observaciones: El usuario a creado una cola y ha sido inicializada y c tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Queue(cola * c, elemento e)
{

	if(c->num_elem == MAX_ELEMENT-1)
	{
		printf("\nERROR: Queue(c,e) desbordamiento de cola.");
		exit(1);
	}
	c->final++;
	if(c->final==MAX_ELEMENT)
		c->final=0;

	c->elementos[c->final] = e;
	c->num_elem++;

	if(c->frente == -1)
	{
		c->frente++;
	}
	return;
}

/*
elemento Dequeue(cola * c);
Descripción: Recibe una cola y devuelve el elemento que se encuentra al
frente de esta, quitándolo de la cola.
Recibe: cola *c (Referencia a la cola "c" a operar)
Devuelve: elemento (Elemento desencolado)
Observaciones: El usuario a creado e inicializado una cola, ademas la cola tiene
elementos, si no es así se genera un error y se termina el programa. (Subdesboramiento de Cola)
*/
elemento Dequeue(cola * c)
{
	elemento e;//Elemento a retornar
	if (c->num_elem>0)
	{
		e=c->elementos[c->frente];
		c->frente++;
		if(c->frente==MAX_ELEMENT)
			c->frente=0;
		c->num_elem--;

		if (c->num_elem == 0)
		{
			c->frente = -1;
			c->final = -1;
		}
	}
	else
	{
		printf("Error:Dequeue(c) subdesbordamiento de cola");
		exit(1);
	}
	//Retornar al elemento
	return e;
}

/*
boolean Empty(cola * c);
Descripción: Recibe una cola y TRUE si la cola esta vacia y FALSE en caso contrario
Recibe: cola *c (Referencia a la cola "c" a verificar)
Devuelve: boolean TRUE O FALSE
Observaciones: El usuario a creado una cola y la cola fue correctamente inicializada
*/
boolean Empty(cola * c)
{

	return (c->num_elem==0)?TRUE:FALSE;
}

/*
elemento Front(cola * c);
Descripción: Recibe una cola y devuelve el elemento que se encuentra al frente de esta.
Recibe: cola *c (Referencia a la cola "c")
Devuelve: elemento del frente de la cola
Observaciones: El usuario a creado una cola,la cola fue correctamente inicializada, esta
tiene elementos de lo contrario devolvera ERROR. *No se modifica el TAD
*/
elemento Front(cola * c)
{
	elemento e;

	if(c->num_elem > 0){
	e=c->elementos[c->frente];
	}else
	{
		printf("Error:Front(c) subdesbordamiento de cola");
		exit(1);
	}

	return e;
}

/*
elemento Final(cola * c);
Descripción: Recibe una cola y devuelve el elemento que se encuentra al final de esta.
Recibe: cola *c (Referencia a la cola "c")
Devuelve: elemento del final de la cola
Observaciones: El usuario a creado una cola,la cola fue correctamente inicializada, esta
tiene elementos de lo contrario devolvera ERROR. *No se modifica el TAD
*/
elemento Final(cola * c)
{
	elemento e;
	if(c->num_elem > 0){
	e=c->elementos[c->final];
	}else
	{
		printf("Error:Final(c) subdesbordamiento de cola");
		exit(1);
	}


	return e;
}

/*
int Size(cola * c);
Descripción: Recibe una cola y devuelve el número de elemento que se encuentran en esta.
Recibe: cola *c (Referencia a la cola "c")
Devuelve: int (Tamaño de la cola)
Observaciones: El usuario a creado una cola,la cola fue correctamente inicializada, esta
*No se modifica el TAD
*/
int Size(cola * c)
{
	int r;
	r=c->num_elem;

	return r;
}

/*
void Element(cola * c, int i);
Descripción: Recibe una cola y un número de elemento de 1 al tamaño de la cola y retorna el elemento de esa posición.
Devuelve: elemento en la posicion i de la cola
Observaciones: El número i debera estar entre 1 y el tamaño de la cola, si esta es vacia o mas pequeña se provoca un error.
*/
elemento Element(cola * c, int i)
{
	elemento r;
	if(i>0 && i<=c->num_elem)
	{
		r=c->elementos[c->frente+(i-1)%MAX_ELEMENT];
	}
	else
	{
		printf("Error:Element(c) indice i fuera de rango");
		exit(1);
	}
	return r;
}

/*
void Destroy(cola * c);
Descripción: Recibe una cola y la libera completamente.
Recibe: cola *c (Referencia a la cola "c" a operar)
Devuelve:
Observaciones: La cola se destruye y se inicializa.
*/
void Destroy(cola * c)
{
	c->num_elem=0;
	c->frente=-1;
	c->final=-1;
	return;
}
