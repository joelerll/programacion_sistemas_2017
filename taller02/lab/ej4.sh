#! /bin/bash

if [ -d $1 ]; then
	echo "si existe"
fi

if [ $USER == 'estudiante' ]; then
	echo "es un estudiantes"
fi


for mi_var in {7..14}; do
	echo $mi_var
done


let s=5+6

echo $((5+9))
echo s
