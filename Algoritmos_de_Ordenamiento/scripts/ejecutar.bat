::@echo off

set BIN=bin
set SRC=numeros1M.txt
set OUT=out\out.txt

%BIN%\rapido.exe 1000000 < %SRC% > %OUT%
