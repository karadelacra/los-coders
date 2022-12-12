/*
Autor: Edgardo Adri�n Franco Mart�nez
Versi�n 1.0 (25 de Septiembre 2012)
Descripci�n: Cabecera de la libreria para recrear presentaciones m�s agradables al usuario en el modo consola

Observaciones: La implementaci�n de esta libreria es distinta si se trata de Windows o Linux, ya que requerir� de funciones no ANSI C
*/
//DECLARACI�N DE FUNCIONES
void MoverCursor( int x, int y ); 	//Funci�n para mover el cursor de escritura de pantalla, simulaci�n de la funci�n gotoxy() que se tenia en borland 3.0 en la libreria conio.h

void EsperarMiliSeg(int t);			//Funci�n para esperar un tiempo en milisegundos, simulaci�n de la funci�n delay() que se tenia en borland 3.0 en la libreria conio.h

void BorrarPantalla(void);			//Funci�n para borrar la pantalla de la consola, simulaci�n de la funci�n clrscr() que se tenia en borland 3.0 en la libreria conio.h
