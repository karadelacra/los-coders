/*
02-sistema-operativo.c
V 1.0 Diciembre 2022
Autores:
    Juan Luis Molina
    Karel Román Padilla
    Danna Lizbeth Matías
    Darío Quiñones

Realiza la simulación de la ejecución de procesos en un sistema
operativo de un solo procesador.

A partir de una lista fija de procesos a realizar, el sistema
operativo progresa en la ejecución de los procesos de acuerdo
a cómo estén encolados.

Después de terminar la tarea de un proceso, el sistema operativo
lo elimina de la cola de procesos y lo agrega a la cola de
procesos terminados.

Se compila de la forma:
    (Linux)
    gcc -o 02-sistema-operativo 02-sistema-operativo.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionLin.c
    (Windows)
    gcc -o 02-sistema-operativo 02-sistema-operativo.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionWin.c

Se ejecuta de la forma:
    ./02-sistema-operativo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../lib/TAD_Cola/TADColaEst.h"
#include "../lib/presentacion.h"

#define INTERVALO_BASE 1000
#define PROCESOS_INICIALES 5

#define POSICION_ACTIVIDAD 23
#define POSICION_CLAVE 60
#define POSICION_TIEMPO 70
#define POSICION_MAX 78
#define POSICION_NOMBRE 84
#define POSICION_CLAVE2 103
#define POSICION_TIEMPO2 113
#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 30
#define MIN_HEIGHT 6
#define MAX_HEIGHT 20

#define POS_ACTIVIDAD 30
#define POS_CLAVE 95
#define POS_TIEMPO 110

#define ANTERIOR 10
#define ACTUAL 31
#define ULTIMO 55

int tamanoprocesos = (POSICION_MAX-2)/3;
/* Estructura de un proceso
    * nombre: Nombre del proceso
    * actividad: Actividad que realiza el proceso
    * ID: Identificador único del proceso
    * tiempo: Tiempo que tarda el proceso en realizar su actividad
    * tiempo_restante: Tiempo que le falta al proceso para terminar su actividad
    * inicio: Tiempo en el que el proceso inició su actividad
    * fin: Tiempo en el que el proceso terminó su actividad
*/
typedef struct proceso{
    char nombre[45];
    char actividad[200];
    char ID[45];
    int tiempo;
    int tiempo_restante;
    time_t inicio;
    time_t fin;
} proceso;

proceso *ProcesoPseudoaleatorio(int procesos_totales);

void ImprimirProceso(proceso *p, int y);
void ImprimirTerminado(proceso *p, int y);
void ImprimirPendiente(proceso *p, int margenizquierda, int margenderecha);
void ImprimirFinal(proceso *p, int y);
void DibujarAdministrador();
void DibujarTerminado();
void BorrarFila(int y);

int main() {
    int i, tiempo = 0, procesos_totales = 0;
    cola procesos, procesos_terminados;
    proceso *p,*p2;
    elemento e;
    bool primero = true;

    // Inicializar semilla de números aleatorios
    srand((unsigned) 1);

    Initialize(&procesos);
    Initialize(&procesos_terminados);
	
    // Crear procesos iniciales
    for (i = 0; i < PROCESOS_INICIALES; i++) {
        p = ProcesoPseudoaleatorio(procesos_totales);
        printf("Proceso %d: %s", i, p->nombre);
        printf(" (%s)", p->ID);
        printf(" - %s", p->actividad);
        printf(" - Tiempo restante: %d\n", p->tiempo_restante);
        procesos_totales++;
        e.p = p;
        Queue(&procesos, e);
    }
	BorrarPantalla();
	DibujarAdministrador();
    // Realizar simulación
    while (!Empty(&procesos))
    {
        EsperarMiliSeg(INTERVALO_BASE);
		//BorrarPantalla();
		
        e = Dequeue(&procesos);
        p = (proceso *)e.p;
        p->tiempo_restante--;
        ImprimirProceso(p,MIN_HEIGHT-1);
        
        if(!primero&&!Empty(&procesos))
        {
        	ImprimirPendiente((proceso *)Final(&procesos).p,ANTERIOR,ACTUAL-1);
		}
		else if(!primero&&Empty(&procesos))
		{
			ImprimirPendiente(p,ANTERIOR,ACTUAL-1);
		}
		primero=false;
        ImprimirPendiente(p,ACTUAL+1,ULTIMO-1);
        if(!Empty(&procesos))
        {
        	ImprimirPendiente((proceso *)Front(&procesos).p,ULTIMO+1,POSICION_MAX-2);
   		}
   		else
   		{
   			ImprimirPendiente(p,ULTIMO+1,POSICION_MAX-2);
		}
        
        for(i=0; i< (MAX_HEIGHT-MIN_HEIGHT+1); i++)
        {
        	if(i<Size(&procesos)&&i<(MAX_HEIGHT-MIN_HEIGHT))
        	{
				p2 = (proceso *)Element(&procesos,i+1).p;
				ImprimirProceso(p2,MIN_HEIGHT+i);
			}
		}
        if (p->tiempo_restante == 0) {
            MoverCursor(25,0);
			printf("Proceso %s %s terminado\n", p->ID, p->nombre);
            time(&p->fin);
            e.p = p;
            Queue(&procesos_terminados, e);
            //p = (proceso *)Final(&procesos_terminados).p;
            MoverCursor(POSICION_NOMBRE,4+Size(&procesos_terminados));
            ImprimirTerminado(p,4+Size(&procesos_terminados));
            if(Size(&procesos)<(MAX_HEIGHT-MIN_HEIGHT)+1)
            {
				BorrarFila(MIN_HEIGHT+Size(&procesos)-1);
			}
        } else {
			//printf("Proceso %s (%s): %d\n", p->ID, p->nombre, p->tiempo_restante);
            e.p = p;
            Queue(&procesos, e);
        }
        tiempo++;
    }
	BorrarPantalla();
	DibujarTerminado();
	i=0;
	
    // Imprimir procesos terminados
    while (!Empty(&procesos_terminados))
    {
        e = Dequeue(&procesos_terminados);
        p = (proceso *)e.p;
        ImprimirFinal(p,5+i);
        i++;
        free(p);
    }
    MoverCursor(0,CONSOLE_HEIGHT-3);
    return 0;
}

void ImprimirProceso(proceso *p, int y)
{
	int i;
	
	MoverCursor(0,y);

    for(i=0; i<POSICION_ACTIVIDAD-1; i++)
    {
    	if(i<strlen(p->nombre))
    	{
			printf("%c",(p->nombre)[i]);
		}
		else
		{
			printf(" ");
		}
	}
    MoverCursor(POSICION_ACTIVIDAD,y);

    for(i=0; i<(POSICION_CLAVE-POSICION_ACTIVIDAD-1); i++)
    {
    	if(i<strlen(p->actividad))
    	{
			printf("%c",(p->actividad)[i]);
		}
		else
		{
			printf(" ");
		}
	}
    MoverCursor(POSICION_CLAVE,y);
    
    for(i=0; i<(POSICION_TIEMPO-POSICION_CLAVE-1); i++)
    {
    	if(i<strlen(p->ID))
    	{
			printf("%c",(p->ID)[i]);
		}
		else
		{
			printf(" ");
		}
	}
    for(i=POSICION_TIEMPO; i<POSICION_MAX-1; i++)
    {
    	MoverCursor(i,y);
    	printf(" ");
	}
	MoverCursor(POSICION_TIEMPO,y);
    printf("%d",p->tiempo_restante);
}

void ImprimirTerminado(proceso *p, int y)
{
	int i;
	
	MoverCursor(POSICION_NOMBRE,y);
	for(i=0; i<POSICION_CLAVE2-POSICION_NOMBRE-1; i++)
    {
    	if(i<strlen(p->nombre))
    	{
			printf("%c",(p->nombre)[i]);
		}
		else
		{
			printf(" ");
		}
	}
	
	MoverCursor(POSICION_CLAVE2,y);
	for(i=0; i<POSICION_TIEMPO2-POSICION_CLAVE2-1; i++)
    {
    	if(i<strlen(p->ID))
    	{
			printf("%c",(p->ID)[i]);
		}
		else
		{
			printf(" ");
		}
	}
	
	MoverCursor(POSICION_TIEMPO2,y);
	printf("%d",(int)(p->fin - p->inicio));
}

void ImprimirPendiente(proceso *p, int margenizquierda, int margenderecha)
{
	int i;
	int j=1;
	
	MoverCursor(margenizquierda,CONSOLE_HEIGHT-6);
	//printf("%s",p->ID);
	for(i=0; i<(margenderecha-margenizquierda+1); i++)
    {
    	if(i<strlen(p->ID))
    	{
			printf("%c",(p->ID)[i]);
		}
		else
		{
			printf(" ");
		}
	}
	MoverCursor(margenizquierda,CONSOLE_HEIGHT-4);
	//printf("%s",p->nombre);
	for(i=0; i<(margenderecha-margenizquierda+1); i++)
    {
    	if(i<strlen(p->nombre))
    	{
			printf("%c",(p->nombre)[i]);
		}
		else
		{
			printf(" ");
		}
	}
	MoverCursor(margenizquierda,CONSOLE_HEIGHT-2);
	for(i=0; i<(margenderecha-margenizquierda+1); i++)
    {
		printf(" ");
	}
	MoverCursor(margenizquierda,CONSOLE_HEIGHT-2);
	printf("%d",p->tiempo_restante);
}

void ImprimirFinal(proceso *p, int y)
{
	int i;
	
	MoverCursor(0,y);

    for(i=0; i<POS_ACTIVIDAD-1; i++)
    {
    	if(i<strlen(p->nombre))
    	{
			printf("%c",(p->nombre)[i]);
		}
		else
		{
			printf(" ");
		}
	}
    MoverCursor(POS_ACTIVIDAD,y);

    for(i=0; i<(POS_CLAVE-POS_ACTIVIDAD-1); i++)
    {
    	if(i<strlen(p->actividad))
    	{
			printf("%c",(p->actividad)[i]);
		}
		else
		{
			printf(" ");
		}
	}
    MoverCursor(POS_CLAVE,y);
    
    for(i=0; i<(POS_TIEMPO-POS_CLAVE-1); i++)
    {
    	if(i<strlen(p->ID))
    	{
			printf("%c",(p->ID)[i]);
		}
		else
		{
			printf(" ");
		}
	}
    for(i=POS_TIEMPO; i<CONSOLE_WIDTH-1; i++)
    {
    	MoverCursor(i,y);
    	printf(" ");
	}
	MoverCursor(POS_TIEMPO,y);
    printf("%d seg",(int)(p->fin - p->inicio));
}

void DibujarAdministrador()
{
	int i;
	
	//Dibujar t�tulos de la tabla
	MoverCursor(2,1);
	printf("PROCESOS PENDIENTES");
	MoverCursor(0,3);
	printf("Nombre");
	MoverCursor(POSICION_ACTIVIDAD,3);
	printf("Actividad",179);
	MoverCursor(POSICION_CLAVE,3);
	printf("ID",179);
	MoverCursor(POSICION_TIEMPO,3);
	printf("Tiempo",179);
	MoverCursor(POSICION_MAX-1,3);
	printf("%c",179);
	
	//Dibujar borde superior
	MoverCursor(0,2);
	for(i = 0; i < POSICION_MAX-1; i++)
	{
		printf("%c",205);
	}
	
	//Dibujar borde medio
	MoverCursor(0,4);
	for(i = 0; i < POSICION_MAX-1; i++)
	{
		printf("%c",196);
	}
	
	//Arreglar detalles
	MoverCursor(POSICION_MAX-1,0);
	printf("%c",186);
	MoverCursor(POSICION_MAX-1,1);
	printf("%c",186);
	MoverCursor(POSICION_MAX-1,2);
	printf("%c",185);
	
	//Dibujar bordes de columnas
	for(i = MIN_HEIGHT-3; i < MAX_HEIGHT; i++)
	{
		MoverCursor(POSICION_ACTIVIDAD-1,i);
		printf("%c",179);
		MoverCursor(POSICION_CLAVE-1,i);
		printf("%c",179);
		MoverCursor(POSICION_TIEMPO-1,i);
		printf("%c",179);
		MoverCursor(POSICION_MAX-1,i);
		printf("%c",186);
	}
	
	//Dibujar borde inferior
	MoverCursor(0,MAX_HEIGHT);
	for(i = 0; i < POSICION_MAX-1; i++)
	{
		printf("%c",205);
	}
	
	//Arreglando detalles
	MoverCursor(POSICION_ACTIVIDAD-1,4);
	printf("%c",197);
	MoverCursor(POSICION_CLAVE-1,4);
	printf("%c",197);
	MoverCursor(POSICION_TIEMPO-1,4);
	printf("%c",197);
	MoverCursor(POSICION_MAX-1,4);
	printf("%c",186);
	
	//-----------------------------------------------------------------//
	//PARTE INFERIOR: PROCESOS EN CURSO, ANTERIOR Y SIGUIENTE
	MoverCursor(0,CONSOLE_HEIGHT-7);
	for(i = 0; i < POSICION_MAX-1; i++)
	{
		printf("%c",205);
	}
	MoverCursor(1,CONSOLE_HEIGHT-6);
	printf("ID");
	MoverCursor(1,CONSOLE_HEIGHT-4);
	printf("Nombre");
	MoverCursor(1,CONSOLE_HEIGHT-2);
	printf("Tiempo");
	
	//Dibujando bordes de columnas
	for(i=CONSOLE_HEIGHT-9;i<CONSOLE_HEIGHT;i++)
	{
		MoverCursor(9,i);
		printf("%c",186);
		MoverCursor(ACTUAL,i);
		printf("%c",186);
		MoverCursor(ULTIMO,i);
		printf("%c",186);
		MoverCursor(POSICION_MAX-1,i);
		printf("%c",186);
	}
	
	//Arreglando detalles
	MoverCursor(ANTERIOR-1,CONSOLE_HEIGHT-10);
	printf("%c",203);
	MoverCursor(ACTUAL,CONSOLE_HEIGHT-10);
	printf("%c",203);
	MoverCursor(ULTIMO,CONSOLE_HEIGHT-10);
	printf("%c",203);
	MoverCursor(POSICION_MAX-1,CONSOLE_HEIGHT-10);
	printf("%c",185);
	MoverCursor(ANTERIOR-1,CONSOLE_HEIGHT-7);
	printf("%c",206);
	MoverCursor(ACTUAL,CONSOLE_HEIGHT-7);
	printf("%c",206);
	MoverCursor(ULTIMO,CONSOLE_HEIGHT-7);
	printf("%c",206);
	MoverCursor(POSICION_MAX-1,CONSOLE_HEIGHT-7);
	printf("%c",185);
	
	//Escribiendo los t�tulos de la tabla
	MoverCursor(ANTERIOR+7,CONSOLE_HEIGHT-9);
	printf("PROCESO");
	MoverCursor(ANTERIOR+7,CONSOLE_HEIGHT-8);
	printf("ANTERIOR");
	MoverCursor(ACTUAL+8,CONSOLE_HEIGHT-9);
	printf("PROCESO");
	MoverCursor(ACTUAL+8,CONSOLE_HEIGHT-8);
	printf("EN CURSO");
	MoverCursor(ULTIMO+7,CONSOLE_HEIGHT-9);
	printf("PROCESO");
	MoverCursor(ULTIMO+7,CONSOLE_HEIGHT-8);
	printf("SIGUIENTE");
	
	//-----------------------------------------------------------------//
	//PARTE DERECHA: PROCESOS TERMINADOS.
	//Dibujar t�tulos de la tabla
	MoverCursor(POSICION_NOMBRE+2,1);
	printf("PROCESOS TERMINADOS");
	MoverCursor(POSICION_NOMBRE,3);
	printf("Nombre");
	MoverCursor(POSICION_CLAVE2,3);
	printf("ID");
	MoverCursor(POSICION_TIEMPO2,3);
	printf("Tiempo");
	
	//Dibujar borde superior
	MoverCursor(POSICION_NOMBRE,2);
	for(i=0; i<CONSOLE_WIDTH-POSICION_NOMBRE; i++)
	{
		printf("%c",205);
	}
	
	//Dibujar bordes de columnas
	for(i=3; i<CONSOLE_HEIGHT; i++)
	{
		MoverCursor(POSICION_NOMBRE-1,i);
		printf("%c",186);
		MoverCursor(POSICION_CLAVE2-1,i);
		printf("%c",179);
		MoverCursor(POSICION_TIEMPO2-1,i);
		printf("%c",179);
	}
	
	//Dibujar borde medio
	MoverCursor(POSICION_NOMBRE,4);
	for(i=0; i<CONSOLE_WIDTH-POSICION_NOMBRE; i++)
	{
		printf("%c",196);
	}
	MoverCursor(POSICION_NOMBRE-1,0);
	printf("%c",186);
	MoverCursor(POSICION_NOMBRE-1,1);
	printf("%c",186);
	MoverCursor(POSICION_NOMBRE-1,2);
	printf("%c",204);
	
	MoverCursor(POSICION_CLAVE2-1,4);
	printf("%c",197);
	MoverCursor(POSICION_TIEMPO2-1,4);
	printf("%c",197);
}

void DibujarTerminado()
{
	int i;
	
	//Dibujar t�tulos de la tabla
	MoverCursor(2,1);
	printf(" PROCESOS TERMINADOS");
	MoverCursor(0,3);
	printf(" Nombre");
	MoverCursor(POS_ACTIVIDAD,3);
	printf(" Actividad",179);
	MoverCursor(POS_CLAVE,3);
	printf(" ID",179);
	MoverCursor(POS_TIEMPO,3);
	printf(" Tiempo",179);
	
	//Dibujar borde superior
	MoverCursor(0,2);
	for(i = 0; i < CONSOLE_WIDTH; i++)
	{
		printf("%c",205);
	}
	
	//Dibujar borde medio
	MoverCursor(0,4);
	for(i = 0; i < CONSOLE_WIDTH; i++)
	{
		printf("%c",196);
	}
	
	//Dibujar bordes de columnas
	for(i = MIN_HEIGHT-3; i < CONSOLE_HEIGHT; i++)
	{
		MoverCursor(POS_ACTIVIDAD-1,i);
		printf("%c",179);
		MoverCursor(POS_CLAVE-1,i);
		printf("%c",179);
		MoverCursor(POS_TIEMPO-1,i);
		printf("%c",179);
	}
	
	//Arreglando detalles
	MoverCursor(POS_ACTIVIDAD-1,4);
	printf("%c",197);
	MoverCursor(POS_CLAVE-1,4);
	printf("%c",197);
	MoverCursor(POS_TIEMPO-1,4);
	printf("%c",197);
}

void BorrarFila(int y)
{
	int i;
	
	MoverCursor(0,y);
	for(i=0; i<POSICION_ACTIVIDAD-1;i++)
	{
		printf(" ");
	}
	MoverCursor(POSICION_ACTIVIDAD,y);
	for(i=0; i<POSICION_CLAVE-POSICION_ACTIVIDAD-1;i++)
	{
		printf(" ");
	}
	MoverCursor(POSICION_CLAVE,y);
	for(i=0; i<POSICION_TIEMPO-POSICION_CLAVE-1;i++)
	{
		printf(" ");
	}
	MoverCursor(POSICION_TIEMPO,y);
	for(i=0; i<POSICION_MAX-POSICION_TIEMPO-1;i++)
	{
		printf(" ");
	}
}

/* proceso ProcesoAleatorio(procesos_totales)
Recibe:
    procesos_totales: el número de procesos totales que se han creado
Retorna un puntero al proceso mallocado

Crea un proceso a partir de un grupo de nombres y actividades predefinidas.
*/
proceso *ProcesoPseudoaleatorio(int procesos_totales) {
    proceso *nuevo_proceso;
    char nombres[15][45] = {
        "Microsoft Word",
        "Microsoft Excel",
        "Microsoft PowerPoint",
        "Task Manager",
        "Google Chrome",
        "Mozilla Firefox",
        "Microsoft Edge",
        "Discord",
        "Spotify",
        "Visual Studio Code",
        "Command Prompt",
        "Adobe Photoshop",
        "Avast Antivirus",
        "Paint",
        "Windows Explorer"
    },
    actividades[15][200] = {
        "Procesando texto enriquecido",
        "Procesando gráficos financieros",
        "Renderizando presentación multimedia",
        "Detectando procesos en ejecución",
        "Cargando página web",
        "Cargando página web",
        "Descargando Google Chrome",
        "Recibiendo mensajes y llamadas",
        "Reproduciendo streaming de audio",
        "Ejecutando código fuente",
        "El comando 'cls' no se reconoce como un comando interno o externo",
        "Editando imagen con filtros",
        "Escaneando archivos",
        "Dibujando formas básicas",
        "Cargando archivos"
    };
    int rand_val;

    nuevo_proceso = (proceso *) malloc(sizeof(proceso));

    rand_val = rand() % 15;
    strcpy(nuevo_proceso->nombre, nombres[rand_val]);
    strcpy(nuevo_proceso->actividad, actividades[rand_val]);
    sprintf(nuevo_proceso->ID, "%03d%c%d", procesos_totales, nombres[rand_val][0], rand() % 10);

    nuevo_proceso->tiempo_restante = rand() % 20 + rand() % 20 + 5;
    nuevo_proceso->tiempo = nuevo_proceso->tiempo_restante;

    time(&nuevo_proceso->inicio);

    return nuevo_proceso;
}
