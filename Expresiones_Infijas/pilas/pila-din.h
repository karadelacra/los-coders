#define TRUE 1
#define FALSE 0

typedef char boolean;

typedef struct elemento
{
	//Lo que el usuario guste
    char dato;
} elemento;

typedef struct nodo
{
	elemento e;
	struct nodo *abajo;
} nodo;

typedef struct pila
{
	int size;
	nodo * tope;
} pila;

/*
Inicializar pila (Initialize): recibe<- pila (S);
Initialize(S);
Efecto: Recibe una pila y la inicializa para su trabajo normal.
*/
void Initialize(pila *S);

/*
Empilar (Push): recibe<- pila (S); recibe<- elemento (e)
Push(S,e);
Efecto: Recibe la pila y aumenta su tamaño, poniendo el elemento en la cima de la pila.
*/
void Push(pila *S,elemento e);

/*
Desempilar (Pop): recibe<- pila (S); retorna -> elemento
e=Pop(S);
Efecto: Recibe la pila, remueve el elemento tope y lo retorna.
Excepción: Si la pila esta vacía, produce error.
*/
elemento Pop(pila *S);

/*
Es vacía (Empty): recibe<- pila (S); retorna -> boolean
b=Empty(S);
Efecto: Recibe una pila y devuelve true si esta vacía y false en caso contrario.
*/
boolean Empty(pila *S);


/*
Tope pila (Top): recibe<- pila (S); retorna -> elemento
e=Top(S);
Efecto: Devuelve el elemento cima de la pila.
Excepción: Si la pila esta vacía produce error
*/
elemento Top(pila *S);


/*
Tamaño pila (Size): recibe<- pila (S); retorna -> tamaño de la pila (entero)
n=Size(S);
Efecto: Devuelve el número de elementos que contiene la pila (Altura de la pila).
*/
int Size(pila *S);

/*
Eliminar pila (Destroy): recibe<- pila (S)
Destroy(S);
Efecto: Recibe una pila y la libera completamente
*/
void Destroy(pila *S);