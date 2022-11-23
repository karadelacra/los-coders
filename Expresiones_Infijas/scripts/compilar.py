# compilar.py
# Version 1.0 22 de Noviembre 2022
# Autor:
#
# Descripcion: Este programa es un script que compila el codigo fuente del proyecto
#              Expresiones Infijas, el cual se encuentra en el directorio encima de
#              este script.
# El script esta pensado para ser ejecutado desde la carpeta principal del proyecto

import os

# # sistema operativo
# so = os.uname().sysname

# Compilar el codigo fuente
compilador = "gcc"
# Opciones extra para el compilador
flags = "-Wall -Wextra -Werror -pedantic -std=c99 -g"

# Dependiendo si se utilizan librerías de la pila dinámica o estática
librerias = "pilas/pila-dinamica.c"
# librerias = "pilas/pila-estatica.c"
output = "-o bin/Expresiones_Infijas"

# Si la carpeta bin no existe, crearla
if not os.path.exists("bin"):
    os.mkdir("bin")

# Asegurarse que el gcc se encuentra instalado
if not os.system("which gcc"):
    # Compilar el codigo fuente
    print("Compilando el codigo fuente...")
    print(f"{compilador} {flags} main.c {librerias} {output}")
    os.system(f"{compilador} {flags} {output} main.c {librerias}")
else:
    print("El compilador gcc no se encuentra instalado")

