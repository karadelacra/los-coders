#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "TADABB.h"
#include "TADListaSL.h"

//inicializar el arbol
void Initializeabb(abb *a)
{
    a->raiz = NULL;
    a->finabb = NULL;
    a->nivel = 0;
}

// Retorna la última posición de la lista
posicionBin Finalabb(abb *a)
{
    return a->finabb;
}

// Retorna la primera posición de la lista
posicionBin Firstabb(abb *a)
{
    return a->raiz;
}

// Retorna la posición del padre dividiendo el valor de la posición /2
posicionBin Parent(abb *a, posicionBin p)
{
    


}

// Retorna la posición del hijo izquierdo multiplicando el valor de la posición *2
posicionBin LeftChild(abb *a, posicionBin p)
{
    return p->izq;
}

// Retorna la posición del hijo derecho multiplicando el valor de la posición *2+1
posicionBin RightChild(abb *a, posicionBin p)
{
    return p->der;
}

// Retorna la posición del elemento que coincida con la palabra
posicionBin Find(abb *a, char *palabra)
{
    posicionBin p = a->raiz;
    while (p != NULL)
    {
        if (strcmp((p->dato).p, palabra) == 0)
        {
            return p;
        }
        else if (strcmp((p->dato).p, palabra) > 0)
        {
            p = p->izq;
        }
        else
        {
            p = p->der;
        }
    }
    return p;
}

// Retorna la definición de la palabra
posicionBin Definition(abb *a, char *palabra)
{
    posicionBin p = a->raiz;
    while (p != NULL)
    {
        if (strcmp((p->dato).p, palabra) == 0)
        {
            return (p->dato).d;
        }
        
    }
    return p;
}

// Retorna si la posición es válida
boolean ValidPositionabb(abb *a, posicionBin p)
{
    if (p == NULL||p>a->finabb)
    {
        return false;
    }
    else
    {
        return true;
    }


    return 0;
}

// Retorna el elemento de la posición
posicionBin Positionabb(abb *a, int indice)
{
    return a->raiz;
}

// Retorna múmero de elementos en la lista
int Sizeabb(abb *a)
{
    return a->finabb;
}

// Retorna si la lista está vacía
boolean Emptyabb(abb *a)
{
    if (a->raiz == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Inserta un elemento en la lista
void Addabb(abb *a, char *palabra, char *definicion)
{
    posicionBin p = a->raiz;
    posicionBin q = NULL;
    posicionBin nuevo = (posicionBin)malloc(sizeof(struct nodo));
    strcpy((nuevo->dato).p, palabra);
    strcpy((nuevo->dato).d, definicion);
    nuevo->izq = NULL;
    nuevo->der = NULL;
    while (p != NULL)
    {
        q = p;
        if (strcmp((p->dato).p, palabra) > 0)
        {
            p = p->izq;
        }
        else
        {
            p = p->der;
        }
    }
    if (q == NULL)
    {
        a->raiz = nuevo;
    }
    else if (strcmp((q->dato).p, palabra) > 0)
    {
        q->izq = nuevo;
    }
    else
    {
        q->der = nuevo;
    }
    a->tam++;
}

// Elimina un elemento de la lista
void Removeabb(abb *a, posicionBin p)
{
    posicionBin q = a->raiz;
    posicionBin r = NULL;
    while (q != NULL)
    {
        if (q == p)
        {
            if (q->izq == NULL && q->der == NULL)
            {
                if (r == NULL)
                {
                    a->raiz = NULL;
                }
            }
            else if (q->izq == NULL)
            {
                if (r == NULL)
                {
                    a->raiz = q->der;
                }
                else if (r->izq == q)
                {
                    r->izq = q->der;
                }
                else
                {
                    r->der = q->der;
                }
            }
            else if (q->der == NULL)
            {
                if (r == NULL)
                {
                    a->raiz = q->izq;
                }
                else if (r->izq == q)
                {
                    r->izq = q->izq;
                }
                else
                {
                    r->der = q->izq;
                }
            }
            else
            {
                posicionBin s = q->der;
                posicionBin t = q;
                while (s->izq != NULL)
                {
                    t = s;
                    s = s->izq;
                }
                q->dato = s->dato;
                if (t == q)
                {
                    t->der = s->der;
                }
                else
                {
                    t->izq = s->der;
                }
                q = s;
            }
            free(q);
            a->tam--;
            return 0;
        }
        else
        {
            r = q;
            if (strcmp((q->dato).p, (p->dato).p) > 0)
            {
                q = q->izq;
            }
            else
            {
                q = q->der;
            }
        }
    }
    return 0;
}