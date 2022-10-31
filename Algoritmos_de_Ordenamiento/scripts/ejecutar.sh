#!/bin/sh

# Un script de shell que ejecuta todos los algoritmos compilados en el directorio bin
# utilizanddo los primeros 100 valores del archivo de entrada numeros1M.txt y
# guardando los resultados en el directorio out, en archivos de texto con el mismo
# nombre que el algoritmo correspondiente.

# Variables
BIN_DIR=bin
SRC=numeros1M.txt
OUT_DIR=out

# Comprobar que el directorio bin existe
if [ ! -d $BIN_DIR ]; then
    echo "El directorio $BIN_DIR no existe, utilice el script compilar.sh para compilar los algoritmos"
    exit 1
fi

# Comprobar que el archivo de entrada existe
if [ ! -f $SRC ]; then
    echo "El archivo $SRC no esta en el directorio actual"
    exit 1
fi

# Crear el directorio de salida
mkdir -p $OUT_DIR

# Ejecutar todos los binarios en el directorio bin
for f in $BIN_DIR/*
do
    echo "Ejecutando $f"
    $f 100 < $SRC > $OUT_DIR/${f##*/}.txt
done