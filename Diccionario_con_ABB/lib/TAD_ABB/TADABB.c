#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "TADABB.h"
//#include "../TAD_Lista/TADListaSL.h"

/***************************************************************************************
								OPERACIONES DE CONSTRUCCI�N
***************************************************************************************/
//inicializar el arbol
int ultimabusqueda;

void Initialize(abb *a)
{
    a->raiz = NULL;
    a->finabb = NULL;
    a->nivel = 0;
    a->tam = 0;
    printf("\n  ARBOL CREADO");
    return;
}
void Destroy(abb *a)
{
	while(a->raiz != NULL)
	{
		Remove(a, Root(a));
	}
    a->finabb = NULL;
    a->nivel = 0;
    a->tam = 0;
    printf("\n  ARBOL DESTRUIDO");
    return;
}
/***************************************************************************************
						OPERACIONES DE POSICIONAMIENTO Y B�SQUEDA
***************************************************************************************/
// Recibe un ABB y devuelve la posici�n de la ra�z.
posicion Root(abb *a)
{
    return a->raiz;
}
// Recibe un ABB a y una posici�n p, devuelve la posici�n de el padre.
posicion Parent(abb *a, posicion p)
{
    return p->padre;
}
// Recibe un ABB a y una posici�n p, devuelve la posici�n del hijo derecho.
posicion RightSon(abb *a, posicion p)
{
    return p->der;
}
// Recibe un ABB a y una posici�n p, devuelve la posici�n del hijo izquierdo.
posicion LeftSon(abb *a, posicion p)
{
    return p->izq;
}
// Recibe un ABB a y un elemento e, devuelve la posici�n del elemento en el �rbol.
posicion Search(abb *a, elemento e)
{
	ultimabusqueda = 0;
	a->ultbusq = 0;
	posicion aux = BuscarPosPalabra(Root(a), e.p);
	a->ultbusq = ultimabusqueda;
	//printf("\n  N%cmero de b%csquedas: %d",163,163,a->ultbusq);
	return aux;
}
// Recibe una posicion p y una palabra[101] y recursivamente busca si la palabra se encuentra en el �rbol
posicion BuscarPosPalabra(posicion nodo, char palabra[101])
{
	posicion aux = NULL;
	if(nodo == NULL){
	}
	else if(strcmp(nodo->dato.p, palabra) == 0){
		aux = nodo;
	}
	else{
		/*if(BuscarPosPalabra(nodo->izq, palabra) != NULL){
			aux = BuscarPosPalabra(nodo->izq, palabra);
		}
		else{
			if(BuscarPosPalabra(nodo->der, palabra) != NULL){
				aux = BuscarPosPalabra(nodo->der, palabra);
			}
		}*/
		if(strcmp(palabra, nodo->dato.p) > 0)
		{
			aux = aux = BuscarPosPalabra(nodo->der, palabra);
		}
		else{
			aux = BuscarPosPalabra(nodo->izq, palabra);
		}
	}
	ultimabusqueda++;
	return aux;
}
/***************************************************************************************
								OPERACIONES DE CONSULTA
***************************************************************************************/
// Retorna si el �rbol est� vac�o.
bool Empty(abb *a)
{
    bool vacio = false;
	if (a->raiz == NULL)
    {
        vacio = true;
    }
    return vacio;
}
// Retorna si la posici�n es v�lida
bool NullNode(abb *a, posicion p)
{
	bool nulo = true;
	if (p != NULL)
    {
        if(BuscarPosicion(Root(a), p) == true)
        {
        	nulo = false;
        }
    }
    printf("\n\n%d",nulo);
    return nulo;
}

bool BuscarPosicion(posicion nodo, posicion p)
{
	bool validar = false;
	bool izquierda = false;
	bool derecha = false;
	if(nodo == NULL){
		
	}
	else if(nodo == p){
		validar = true;
	}
	else{
		izquierda = BuscarPosicion(nodo->izq, p);
		if (izquierda){
			validar = true;
		}
		else{
			derecha = BuscarPosicion(nodo->der, p);
			if (derecha){
				validar = true;
			}
		}
	}
	return validar;
}
// Retorna el n�mero de elementos en el ABB.
int Size(abb *a)
{
    return a->tam;
}
// Recibe un ABB y una posici�n p, regresa el elemento en dicha posici�n.
elemento Element(abb *a, posicion p)
{
	return p->dato;
}
// Recibe una posici�n e imprime el PreOrden de los elementos del �rbol a partir de la posici�n dada.
void RecorridoPreOrden(nodoBin *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	printf("%s, ",nodo->dato.p);
	RecorridoPreOrden(nodo->izq);
	RecorridoPreOrden(nodo->der);
}
// Recibe una posici�n e imprime el InOrden de los elementos del �rbol a partir de la posici�n dada.
void RecorridoInOrden(nodoBin *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	RecorridoInOrden(nodo->izq);
	printf("%s, ",nodo->dato.p);
	RecorridoInOrden(nodo->der);
}
// Recibe una posici�n e imprime el PostOrden de los elementos del �rbol a partir de la posici�n dada.
void RecorridoPosOrden(nodoBin *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	RecorridoPosOrden(nodo->izq);
	RecorridoPosOrden(nodo->der);
	printf("%s, ",nodo->dato.p);
}

int altura(nodoBin *nodo)
{
	if(nodo==NULL){
		return 0;}
	int alt_izq = altura(nodo->izq);
	int alt_der = altura(nodo->der);
	if(alt_izq>alt_der){
		return alt_izq + 1;}
	else{
		return alt_der + 1;
	}
}
/***************************************************************************************
							    OPERACIONES DE MODIFICACI�N
***************************************************************************************/
// Inserta un elemento en el �rbol
void Add(abb *a, elemento e)
{
    if(Search(a, e) != NULL)
    {
    	printf("\n YA EXISTE LA PALABRA");
    	return;
	}
	bool EsDerecho;
    posicion nuevo;
    posicion aux = a->raiz;
    posicion aux2 = NULL;
	printf("\n Palabra: %s\tDefinicion: %s", e.p, e.d);
    nuevo = (posicion)malloc(sizeof(struct nodoBin));
    nuevo->padre = NULL;
	nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->dato = e;
	if (Empty(a) == true)
    {
    	a->raiz = nuevo;
	}
	else
	{
		while(aux != NULL)
		{
			aux2 = aux;	
			if(strcmp(e.p, aux->dato.p) > 0)
			{
				EsDerecho = true;
				aux = aux->der;
				//printf("\n ES DERECHO");
			}
			else
			{
				EsDerecho = false;
				aux = aux->izq;
				//printf("\n ES IZQUIERDO");
			}
		}
		if(EsDerecho)
		{
			aux2->der = nuevo;
		}
		else
		{
			aux2->izq = nuevo;
		}
		nuevo->padre = aux2;
	}
	a->tam++;
}
// Reemplaza la definici�n de una palabra.
void ReplaceDefinition(abb *a, posicion p, char def[251])
{
	strcpy(p->dato.d, def);
	return;
}
// Elimina un elemento de la lista
void Remove(abb *a, posicion p)
{
	posicion aux = p;
	posicion aux2;
	a->tam--;
	
	if(p->izq == NULL && p->der == NULL)
	{
		if(aux == Root(a))
		{
			//printf("\n Borrado %s", p->dato.p);
			a->raiz = NULL;
			free(aux);
			return;
		}
		aux2 = Parent(a, aux);
		if(aux2->izq == aux)
		{
			aux2->izq = NULL;
		}
		if(aux2->der == aux)
		{
			aux2->der = NULL;
		}
		//printf("\n Borrado %s", p->dato.p);
		//printf("\nTRUENA");
		free(aux);
	}
	else if((p->izq == NULL && p->der != NULL) || (p->izq != NULL && p->der == NULL))
	{
		aux2 = Parent(a, aux);
		if(aux2->izq == aux)
		{
			if(aux->izq != NULL)
			{
				aux2->izq = aux->izq;
			}
			if(aux->der != NULL)
			{
				aux2->izq = aux->der;
			}
			aux->izq->padre = aux2;
		}
		if(aux2->der == aux)
		{
			if(aux->izq != NULL)
			{
				aux2->der = aux->izq;
			}
			if(aux->der != NULL)
			{
				aux2->der = aux->der;
			}
			aux->der->padre = aux2;
		}
		//printf("\n Borrado %s", p->dato.p);
		free(aux);
	}
	else
	{
		aux = aux->der;
		while(aux->izq != NULL)
		{
			aux = aux->izq;
		}
		if(aux->padre->izq == aux)
		{
			p->dato = aux->dato;
			aux->padre->izq = NULL;
			//printf("\n Borrado %s", p->dato.p);
			
			free(aux);
		}
		else
		{
			elemento e2;
			
			e2 = p->dato;
			p->dato = aux->dato;
			aux->dato = e2;
			a->tam++;
			Remove(a, aux);
		}
		
		//p->dato = aux->dato;
		//aux->padre->izq = NULL;
		//free(aux);


	}
	
}
/***************************************************************************************
						  OPERACIONES DE CONSULTA (DEPURACI�N)
***************************************************************************************/
void VerLigas(abb *a)
{
	int i = 0;
	posicion aux;	
	aux=Root(a);
	printf("\n*****************************************************************************************************");
	InOrdenDetallado(aux);
	printf("\n*****************************************************************************************************");
	printf("\n  Ra%cz del %crbol: %s",161, 160,aux->dato.p);
	printf("\n  Altura del %crbol: %d", 160, altura(Root(a)));
	printf("\n  Cantidad de elementos=%d",a->tam);
	return;
}

void PreOrdenDetallado(nodoBin *nodo)
{
	if(nodo == NULL)
	{
		printf("\nNULL");
		return;
	}
	printf("\nNO DEBERIA");
	Detalles(nodo);
	PreOrdenDetallado(nodo->izq);
	PreOrdenDetallado(nodo->der);
}

void InOrdenDetallado(nodoBin *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	InOrdenDetallado(nodo->izq);
	Detalles(nodo);
	InOrdenDetallado(nodo->der);
}

void PosOrdenDetallado(nodoBin *nodo)
{
	if(nodo == NULL)
	{
		return;
	}
	PosOrdenDetallado(nodo->izq);
	PosOrdenDetallado(nodo->der);
	Detalles(nodo);
}

void Detalles(nodoBin *nodo)
{
	printf("\nPos=%d\t",nodo);
	printf("Padre=");
	if(nodo->padre == 0){
		printf("\033[31m%d\033[0m\t\t", nodo->padre);
	}
	else{
		printf("%s\t\t",nodo->padre->dato.p);
	}
	printf("HijoIzq=");
	if(nodo->izq == 0){
		printf("\033[31m%d\033[0m\t", nodo->izq);
	}
	else{
		printf("%s\t",nodo->izq->dato.p);
	}
	printf("HijoDer=");
	if(nodo->der == 0){
		printf("\033[31m%d\033[0m\t", nodo->der);
	}
	else{
		printf("%s\t",nodo->der->dato.p);
	}
	printf("Palabra: %s",nodo->dato.p);
}
