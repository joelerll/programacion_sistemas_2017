#!/bin/bash
QUIEN="bash script"

DIRECTORIO=/home/estudiante

NOMBRE='JOEL'
MENSAJE="hola $NOMBRE"

LITERAL="Mensaje \t\nLiteral"

ls -la $DIRECTORIO

echo $MENSAJE
echo $LITERAL


echo "mi nombre es $1"


MIVAR=$(date)
echo $MIVAR
