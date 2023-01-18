#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stdbool.h>
#include "../TAD_ABB/TADABB.h"
//#include "TADListaSL.h"

#define TAM_TABLA 20

// Estructura de la tabla hash abierta, que es un arreglo de listas
typedef struct {
    abb arboles[TAM_TABLA];
    int colisiones[TAM_TABLA];
    int elementos;
    int profundidad;
} TablaHash;

// Inicializa la tabla hash
void inicializarTablaHash(TablaHash *t);

// Inserta un elemento en la tabla hash
void insertarTablaHash(TablaHash *t, elemento e);

// Modifica un elemento de la tabla hash
void modificarTablaHash(TablaHash *t, elemento e, int *comps);

// Busca un elemento en la tabla hash, regresa un elemento vacío si no lo encuentra
elemento buscarTablaHash(TablaHash *t, char *clave, int *comps);

// Elimina un elemento de la tabla hash
bool eliminarTablaHash(TablaHash *t, char *clave, int *comps);

// Libera la memoria de la tabla hash
void liberarTablaHash(TablaHash *t);

// Imprime la tabla hash
void imprimirTablaHash(TablaHash *t);






void ImprimirPre(TablaHash *t);


/* Funciones auxiliares */

// Función de hash
int hash(char *clave);

// Busca un elemento en la lista donde su clave es igual a la clave que se busca
posicion BuscarLlave(abb *a, char *clave, int *comps);

#endif
