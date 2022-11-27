#include <stdlib.h>
#include <stdio.h>
#include "pila-din.h"

/*
Inicializar pila (Initialize): recibe<- pila (s);
Initialize(s);
Efecto: Recibe una pila y la inicializa para su trabajo normal.
*/
void Initialize(pila *s)
{
    s->size = 0;
    (*s).tope = NULL;
    return;
}

/*
Empilar (Push): recibe<- pila (s); recibe<- elemento (e)
Push(s,e);
Efecto: Recibe la pila y aumenta su tamaño, poniendo el elemento en la cima de la pila.
*/
void Push(pila *s, elemento e)
{
    nodo *aux;

    aux = malloc(sizeof(nodo));

    if (aux != NULL)
    {
        s->size++;
        aux->e = e;
        aux->abajo = s->tope;
        s->tope = aux;
    }
    else // Desbordamiento de pila
    {
        printf("\nERROR Push(s,e):\"Desbordamiento de pila\"");
        exit(1);
    }
    return;
}

/*
Desempilar (Pop): recibe<- pila (s); retorna -> elemento
e=Pop(s);
Efecto: Recibe la pila, remueve el elemento tope y lo retorna.
Excepción: si la pila esta vacía, produce error.
*/
elemento Pop(pila *s)
{
    elemento r;
    nodo *aux;
    if (s->tope != NULL)
    {
        r = s->tope->e;
        aux = s->tope;
        s->tope = s->tope->abajo; // s->tope=aux->abajo
        free(aux);
        s->size--;
    }
    else // Subdesbordamiento de la pila
    {
        printf("\nERROR e=Pop(s):\"Subdesbordamiento de pila\"");
        exit(1);
    }

    return r;
}

/*
Es vacía (Empty): recibe<- pila (s); retorna -> boolean
b=Empty(s);
Efecto: Recibe una pila y devuelve true si esta vacía y false en caso contrario.
*/
boolean Empty(pila *s)
{
    boolean r;
    if (s->tope != NULL)
        r = FALSE;
    else
        r = TRUE;

    return r;
}

/*
Tope pila (Top): recibe<- pila (s); retorna -> elemento
e=Top(s);
Efecto: Devuelve el elemento cima de la pila.
Excepción: si la pila esta vacía produce error
*/
elemento Top(pila *s)
{
    elemento r;
    if (s->tope != NULL)
    {
        r = s->tope->e;
    }
    else // Subdesbordamiento de la pila
    {
        printf("\nERROR e=Top(s):\"Subdesbordamiento de pila\"");
        exit(1);
    }

    return r;
}

/*
Tamaño pila (size): recibe<- pila (s); retorna -> tamaño de la pila (entero)
n=size(s);
Efecto: Devuelve el número de elementos que contiene la pila (Altura de la pila).
*/
int Size(pila *s)
{
    int r = s->size;
    /*int r=0;
    nodo *aux;
    aux=s->tope;
    while(aux!=NULL)
    {
        r++;
        aux=aux->abajo;
    }
*/
    return r;
}

/*
Eliminar pila (Destroy): recibe<- pila (s)
Destroy(s);
Efecto: Recibe una pila y la libera completamente
*/
void Destroy(pila *s)
{
    nodo *aux;
    if (s->tope != NULL)
    {
        do
        {
            aux = s->tope->abajo;
            free(s->tope);
            s->tope = aux;
        } while (aux != NULL);
    }
    s->size = 0;
    return;
}
