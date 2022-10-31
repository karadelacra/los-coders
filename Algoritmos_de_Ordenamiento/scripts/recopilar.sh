#!/bin/sh
# recopilar.sh
# Version 1.0 Octubre 2022
# Autor: Darío Quiñones

# Un script de shell que ejecuta uno de los algoritmos compilados en el directorio bin
# utilizanddo cantidades progresivas de valores del archivo de entrada numeros1M.txt y
# guardando el tiempo de ejecución de cada test en el directorio out, en archivos de texto
# con el mismo nombre que el algoritmo correspondiente.

# A requerimento del profesor, se utilizan cantidades específicas:
CANTIDADES=(500 1000 5000 10000 50000 100000 200000 500000 1000000)


# Algoritmo a utilizar
ALGORITMO=merge

BIN_DIR=bin # Directorio de binarios
SRC=numeros1M.txt # Archivo de entrada
OUT_DIR=out # Directorio de salida

RESULTADOS=$OUT_DIR/$ALGORITMO.txt # Archivo de resultados
TIEMPOS=out/tiempos-$ALGORITMO.csv # Archivo de tiempos recolectados

# Comprobar que el algoritmo existe
if [ ! -f $BIN_DIR/$ALGORITMO ]; then
    echo "El algoritmo $ALGORITMO no existe, utilice el script compilar.sh para compilar los algoritmos"
    echo "'bash scripts/compilar.sh' para compilar los algoritmos desde la raíz del proyecto"
    exit 1
fi

# Comprobar que el directorio bin existe
if [ ! -d $BIN_DIR ]; then
    echo "El directorio $BIN_DIR no existe, utilice el script compilar.sh para compilar los algoritmos"
    echo "'bash scripts/compilar.sh' para compilar los algoritmos desde la raíz del proyecto"
    exit 1
fi

# Comprobar que el archivo de entrada existe
if [ ! -f $SRC ]; then
    echo "El archivo $SRC no esta en el directorio actual"
    exit 1
fi

# Crear el directorio de salida
mkdir -p $OUT_DIR

# Escribir encabezado del archivo de tiempo
echo "valores,tiempo" > $TIEMPOS

# Ejecutar el binario del algoritmo para cada cantidad de valores

for i in ${CANTIDADES[@]}
do
    echo "Ejecutando '$ALGORITMO' con $i valores"
    # Debido a las variaciones en el tiempo de ejecución, se ejecutan 5 veces para 500 y 1000 valores.
    if [ $i -eq 500 ] || [ $i -eq 1000 ]; then
        for j in {1..5}
        do
            $BIN_DIR/$ALGORITMO $i < $SRC > $RESULTADOS
            # Añadimos la cantidad de valores y el nombre del algoritmo
            echo -n "$i, " >> $TIEMPOS

            # El tiempo de ejecución se encuentra en la última línea del archivo de salida
            # Usando el comando "tail -n 1", obtenemos la última línea del archivo
            # Está en el formato: "Tiempo de ejecución: 0.000000 segundos"
            # Por lo que se utiliza "grep" para aplicar una expresión regular y obtener el valor
            tail -n 1 $RESULTADOS | grep -o '[0-9]*\.[0-9]*0' >> $TIEMPOS
        done
    else
        # Para los demás valores, se ejecutan una sola vez.
        $BIN_DIR/$ALGORITMO $i < $SRC > $RESULTADOS
        # Añadimos la cantidad de valores y el nombre del algoritmo
        echo -n "$i, " >> $TIEMPOS
        # Y el tiempo de ejecución
        tail -n 1 $RESULTADOS | grep -o '[0-9]*\.[0-9]*0' >> $TIEMPOS
    fi
done