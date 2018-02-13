#! /bin/bash

DIRECTORY=files/aleatorio
COPIADO=copiados
if [ ! -d "$DIRECTORY" ]; then
  echo "La carpeta no existe"
  exit 1
fi

if [ ! -d "$COPIADO" ]; then
  echo "Carpeta creada"
  mkdir copiados
fi

i="0"

maximo=48
a=1
b=2

echo -n "Ingrese el puerto [ENTER]: "
read port

# stuff
numero_for=0
start=$(date +%s.%N)
iteraciones=0
while [ $iteraciones -lt 500 ];
do
    if [ $i -gt $maximo ];then
        i=0
        # rm copiados/*
    fi
    let i=$i+1
    let iteraciones=$iteraciones+1
    if [ $? -ne 0 ];then
        echo "todo bien"
    fi
    {
        ./bin/cliente 127.0.0.1 $port files/aleatorio/archivo$i copiados/archivo$i
    }
    # sleep 1
done
end=$(date +%s.%N)
runtime=$(python -c "print(${end} - ${start})")
echo -e "\e[31mEl tiempo fue $runtime\e[0m"
start=$(date +%s.%N)