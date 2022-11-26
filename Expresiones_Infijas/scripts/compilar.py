# compilar.py
# Version 1.0 22 de Noviembre 2022
# Autor:
#
# Descripcion: Este programa es un script que compila el codigo fuente del proyecto
#              Expresiones Infijas, el cual se encuentra en el directorio encima de
#              este script.
# El script esta pensado para ser ejecutado desde la carpeta principal del proyecto

import os

# Dependiendo si se utilizan librerías de la pila dinámica o estática
# Colocado aquí para que sea más fácil cambiarlo
librerias = "pilas/pila-dinamica.c"
# librerias = "pilas/pila_estatica.c"

def main():
    # # sistema operativo
    # so = os.uname().sysname

    # Compilar el codigo fuente
    compilador = "gcc"

    # Opciones extra para el compilador
    # -std=c99: para que el compilador use el estandar C99
    # -Wall: para que el compilador habilite más warnings
    # -pedantic: para que el compilador muestre warnings para adherirse al estandar ansi C
    # -g: para que el compilador genere informacion para el debugger
    # -lm: para que el compilador linkee con la libreria matematica
    flags = "-std=c99 -Wall -Wextra -pedantic -g -lm"

    # librerias = "pilas/pila-estatica.c"
    output = "-o bin/Expresiones_Infijas"

    # Si la carpeta bin no existe, crearla
    if not os.path.exists("bin"):
        os.mkdir("bin")

    # Asegurarse que el gcc se encuentra instalado
    if not os.system("which gcc"):
        # Compilar el codigo fuente
        print("Compilando el codigo fuente...")
        print(f"{compilador} {flags} {output} main.c {librerias}")
        os.system(f"{compilador} {flags} {output} main.c {librerias}")
    else:
        print("El compilador gcc no se encuentra instalado")

# Si este script es ejecutado, ejecutar la funcion main
if __name__ == "__main__":
    main()