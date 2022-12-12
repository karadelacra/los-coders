/*
03-banco.c
V 1.0 Diciembre 2022
Autores:
    Juan Luis Molina
    Karel Román Padilla
    Danna Lizbeth Matías
    Darío Quiñones

Realiza la simulación de un banco con múltiples cajas de atención y
clientes que tienen prioridades diferentes.

* El banco cuenta con 1 a 10 cajas de atención.
* Existen 3 tipos de clientes:
    - Clientes del banco
    - Usuarios del banco
    - Clientes preferentes
* Los clientes preferentes tienen prioridad sobre los demás.
* Los clientes del banco tienen prioridad sobre los usuarios.

Al iniciar la simulación se toman los siguientes datos:
* Número de cajas de atención
* Tiempo de atención en milisegundos de cada caja
* Intervalo de llegada de clientes
* Intervalo de llegada de usuarios
* Intervalo de llegada de clientes preferentes

El estado de las cajas se mostrará gráficamente en la consola.

Se compila de la forma:
    (Linux)
    gcc -o 03-banco 03-banco.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionLin.c
    (Windows)
    gcc -o 03-banco 03-banco.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionWin.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/TAD_Cola/TADColaEst.h"
#include "../lib/presentacion.h"

#define MAX_CAJAS 10
#define MAX_CLIENTES 100
#define INTERVALO_BASE 10

// Estructuras

/*Estructura para representar una caja del banco
cliente: Cliente que está siendo atendido
tiempo_restante: Tiempo que le falta a la caja para terminar de atender al cliente*/
typedef struct caja {
    elemento cliente;
    int tiempo_restante;
}caja;

/*Estructura para representar una fila del banco
clientes: Cola de clientes de la fila
intervalo_llegada: Intervalo de tiempo en el que llegan los clientes
clientes_recibidos: Número de clientes que han llegado a la fila
tiempo_esperando: Tiempo que han estado los clientes esperando en la fila sin ser atendidos*/
typedef struct fila {
    cola clientes;
    int intervalo_llegada;
    int clientes_recibidos;
    int tiempo_esperando;
}fila;

// Prototipos de Función
void escanear_datos(int *num_cajas, int *tiempo_atencion, int intervalos_llegada[3]);
caja *inicializar_cajas(int num_cajas);
void inicializar_filas(fila filas[3], int intervalos_llegada[3]);
void llegada_clientes(fila filas[3], int tiempo);
int atender_clientes(caja *cajas, int num_cajas, fila filas[3], int tiempo_atencion);

int main(void)
{
    caja *cajas;
    fila filas[3];
    int i, clientes_atendidos = 0, tiempo = 0;
    int num_cajas, tiempo_atencion;
    bool banco_vacio = true;
    // Intervalos de llegada ordenados de mayor a menor prioridad
    // 0: Clientes preferentes
    // 1: Clientes del banco
    // 2: Usuarios del banco
    int intervalos_llegada[3];

    // Escanea los datos de entrada
    escanear_datos(
        &num_cajas,
        &tiempo_atencion,
        intervalos_llegada);

    tiempo_atencion /= INTERVALO_BASE;
    printf("Tiempo de atención: %d\n", tiempo_atencion);

    // Inicializar las cajas y las filas
    cajas = inicializar_cajas(num_cajas);
    inicializar_filas(filas, intervalos_llegada);

    // Comenzar simulación
    while (clientes_atendidos <= 100 || !banco_vacio)
    {
        // Incrementar tiempo
        EsperarMiliSeg(INTERVALO_BASE);
        tiempo++;
        printf("T: %d, Clientes Atendidos: %d\n", tiempo, clientes_atendidos);

        // Llegada de clientes en intervalos de tiempo
        llegada_clientes(filas, tiempo);

        // Atender clientes
        clientes_atendidos += atender_clientes(cajas, num_cajas, filas, tiempo_atencion);
        for (i = 0; i < num_cajas; i++)
        {
            printf("Caja %d: ", i + 1);
            printf("Cliente: %c%d ", cajas[i].cliente.tipo, cajas[i].cliente.n);
            printf("Tiempo restante: %d\n", cajas[i].tiempo_restante);
        }

        banco_vacio = (
            Empty(&filas[0].clientes) && Empty(&filas[1].clientes) && Empty(&filas[2].clientes) &&
            cajas[0].cliente.n == -1 && cajas[1].cliente.n == -1 && cajas[2].cliente.n == -1
        );
    }
    printf("El banco cerro, despues de atender a %d clientes\n", clientes_atendidos);
    printf("Tiempo total: %d\n", tiempo);

    return 0;
}

/* void escanear_datos(int *num_cajas, int *tiempo_atencion, int intervalos_llegada[3])
Recibe:
    num_cajas: Puntero a la variable donde se guardará el número de cajas
    tiempo_atencion: Puntero a la variable donde se guardará el tiempo de atención
    intervalos_llegada: Arreglo donde se guardarán los intervalos de llegada

Escanea los datos de entrada y los guarda en las variables correspondientes
en el orden: número de cajas, tiempo de atención, intervalo de llegada de clientes,
intervalo de llegada de usuarios del banco y intervalo de llegada de clientes preferentes.

Pero se guardan por orden de prioridad en el arreglo intervalos_llegada.*/
void escanear_datos(int *num_cajas, int *tiempo_atencion, int intervalos_llegada[3])
{
    int i;
    // printf("Número de cajas de atención: ");
    scanf("%d", num_cajas);
    // Verifica que el número de cajas no sea inválido
    if (*num_cajas < 0 || *num_cajas > MAX_CAJAS)
    {
        printf("El número de cajas debe estar entre 0 y %d.\n", MAX_CAJAS + 1);
        exit(1);
    }

    // printf("Tiempo de atención en milisegundos: ");
    scanf("%d", tiempo_atencion);
    // Verifica que el tiempo de atención sea válido
    if (*tiempo_atencion < 1)
    {
        printf("El tiempo de atención debe ser mayor a 0.\n");
        exit(1);
    }
    if (*tiempo_atencion % 10 != 0)
    {
        printf("El tiempo de atención debe ser múltiplo de 10ms.\n");
        exit(1);
    }

    // Es conveniente que los intervalos estén ordenados de de mayor a menor prioridad
    // A pesar de que se reciben en la forma 1, 2, 3 se guardan en el arreglo como 2, 3, 1
    scanf("%d", &intervalos_llegada[1]);
    scanf("%d", &intervalos_llegada[2]);
    scanf("%d", &intervalos_llegada[0]);

    // Verifica que el intervalo de llegada sea válido
    for (i = 0; i < 3; i++)
    {
        if (intervalos_llegada[i] < 1 && intervalos_llegada[i] % 10 == 0)
        {
            printf("El intervalo de llegada debe ser mayor a 0.\n");
            printf("El intervalo de llegada debe ser múltiplo de 10ms.\n");
            exit(1);
        }
    }
}

/* void inicializar_filas(fila filas[3], int intervalos_llegada[3])
Recibe:
    filas: Arreglo de filas de clientes
    intervalos_llegada: Arreglo con los intervalos de llegada para cada tipo de cliente

Inicializa las filas de clientes con los intervalos de llegada y los tiempos de espera.*/
void inicializar_filas(fila filas[3], int intervalos_llegada[3])
{
    int i;
    for (i = 0; i < 3; i++)
    {
        Initialize(&filas[i].clientes);
        filas[i].intervalo_llegada = intervalos_llegada[i] / INTERVALO_BASE;
        filas[i].clientes_recibidos = 0;
        filas[i].tiempo_esperando = 0;
    }
}

/* caja *inicializar_cajas(int num_cajas)
Recibe:
    num_cajas: Número de cajas
Retorna:
    cajas: Arreglo de cajas inicializadas

Inicializa las cajas con los tiempos de atención y los clientes atendidos.*/
caja *inicializar_cajas(int num_cajas)
{
    int i;
    caja *cajas = (caja *)malloc(sizeof(caja) * num_cajas);
    if (cajas == NULL)
    {
        printf("No se pudo reservar memoria para las cajas.\n");
        exit(1);
    }
    for (i = 0; i < num_cajas; i++)
    {
        cajas[i].cliente.tipo = ' ';
        cajas[i].cliente.n = -1;
        cajas[i].tiempo_restante = 0;
    }
    return cajas;
}

/* void llegada_clientes(fila filas[3], int tiempo)
Recibe:
    filas: Arreglo de filas de clientes
    tiempo: Tiempo actual

Genera los clientes que llegan en el tiempo actual y los agrega a la cola de clientes.*/
void llegada_clientes(fila filas[3], int tiempo)
{
    elemento cliente;
    char tipos[] = {'P', 'C', 'U'};
    int i;
    for (i = 0; i < 3; i++)
    {
        if (tiempo % filas[i].intervalo_llegada == 0)
        {
            // Generar cliente
            cliente.tipo = tipos[i];
            cliente.n = ++(filas[i].clientes_recibidos);

            // Agregar cliente a la cola de clientes
            Queue(&(filas[i].clientes), cliente);
            printf("Llegó el cliente %c%d\n", cliente.tipo, cliente.n);
        }
    }
}

/* int atender_clientes(caja *cajas, int num_cajas, fila filas[3], int tiempo_atencion)
Recibe:
    cajas: Arreglo de cajas
    num_cajas: Número de cajas
    filas: Arreglo de filas de clientes
    tiempo_atencion: Tiempo de atención en milisegundos
Retorna:
    clientes_atendidos: Número de clientes atendidos en el tiempo actual

Atiende a los clientes que están en las cajas y los libera si ya terminó su tiempo de atención.*/
int atender_clientes(caja *cajas, int num_cajas, fila filas[3], int tiempo_atencion)
{
    int i, j, f, clientes_atendidos = 0;
    bool no_han_esperado_mucho, fila_clientes_vacia;
    for (i = 0; i < num_cajas; i++)
    {
        // Si la caja está ocupada
        if (cajas[i].tiempo_restante > 0)
        {
            // Decrementar el tiempo restante
            cajas[i].tiempo_restante--;
            // Si se liberó la caja
            if (cajas[i].tiempo_restante == 0)
            {
                // El cliente ha sido atendido
                clientes_atendidos++;
                // Mostrar mensaje de atención
                printf("En la caja %d se atendió el cliente %c%d\n",
                    i + 1,
                    cajas[i].cliente.tipo,
                    cajas[i].cliente.n);
                cajas[i].cliente.tipo = ' ';
                cajas[i].cliente.n = -1;
            }
        }
        // Si la caja ya está libre, o se acaba de liberar
        if (cajas[i].tiempo_restante == 0)
        {
            // Escoger la cola con mayor prioridad sin que las otras dos tengan clientes esperando

            // Si la fila Preferente tiene clientes y
            // las otras dos tienen menos de 4 turnos esperando
            // si la fila de clientes está vacía, la fila de usuarios puede esperar un turno más
            no_han_esperado_mucho = filas[1].tiempo_esperando < 4 && filas[2].tiempo_esperando < 4;
            fila_clientes_vacia = Empty(&filas[1].clientes) && filas[2].tiempo_esperando < 5;
            if (!Empty(&filas[0].clientes) && (no_han_esperado_mucho || fila_clientes_vacia))
                f = 0;
            else if (!Empty(&filas[1].clientes) && filas[2].tiempo_esperando < 5)
                f = 1;
            else if (!Empty(&filas[2].clientes))
                f = 2;
            else
                f = -1;

            // Mandar a la caja el primer cliente de la fila
            if (f != -1)
            {
                cajas[i].cliente = Dequeue(&filas[f].clientes);
                cajas[i].tiempo_restante = tiempo_atencion;
                printf("En la caja %d se atenderá al cliente %c%d\n",
                    i + 1,
                    cajas[i].cliente.tipo,
                    cajas[i].cliente.n);

                filas[f].tiempo_esperando = 0;
                // Incrementar el tiempo que han esperado los clientes en las otras filas
                for (j = 0; j < 3; j++)
                    if (j != f && !Empty(&filas[j].clientes))
                        filas[j].tiempo_esperando++;
            }
        }
    }
    return clientes_atendidos;
}

