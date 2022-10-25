
@echo off

rem este programa compila todos los archivos 
rem.c del directorio arriba del actual 

:: Variable de la carpeta de binarios
set BIN=bin

gcc rapido.c -o %BIN%\rapido.exe
gcc burbuja.c -o %BIN%\burbuja.exe
gcc insercion.c -o %BIN%\insercion.exe
gcc seleccion.c -o %BIN%\seleccion.exe
rem gcc shell.c -o %BIN%\shell.exe
