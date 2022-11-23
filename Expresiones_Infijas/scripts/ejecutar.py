# compilar.py
# Version 1.0 22 de Noviembre 2022
# Autor:
#
# Descripcion: Este programa es un script que le manda diferentes test cases al programa

import os

# Sisterma operativo
SistemaOperativo = os.uname().sysname

ejecutable = "bin/Expresiones_Infijas"
expresiones = [
    "1+2",
    "1+2*3",
    "1+2*3+4",
]
#     # con parentesis
#     "(1+2)*3",
#     "(1+2)*(3+4)",
#     "(1+2 )* 3)",
#     "(1+2)*(3+4",
#     "( 1 + 2 )*( 3+ 4)"
#     # Con incógnitas
#     "A+B",
#     "A+B*C",
#     # Con números negativos
#     "-1+2",
#     "-1+2*3",
#     # Con todos
#     "A+B*C-D",
#     "A+B*C-D+E(F+G)",
# ]


for expresion in expresiones:
    print(f"Test case: {expresion}")

    if SistemaOperativo == "Linux":
        os.system(f"./{ejecutable} '{expresion}'")
    else:
        os.system(f"{ejecutable} '{expresion}'")
    # Sleep a second
    os.system("sleep 1")