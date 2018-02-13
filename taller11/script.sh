#! /bin/bash
if ! [ -x "$(command -v gnuplot)" ]; then
   echo 'Error: gnuplot no esta instalado, porfavor instalarlo' >&2
   exit 1
fi
echo -n "Ingrese el tamano del array [ENTER]: "
read nArreglo

if [ -f datosHvsT.dat ]; then
    rm -r datosHvsT.dat
fi

make
echo -n "Preparando la salida "
echo ""
sleep 5s
for (( i=2; i <= 16; i+=2 ))
do
  TEST_OUT=$(./bin/hilos $nArreglo $i 2>&1)
  echo $TEST_OUT >> datosHvsT.dat
  echo "Numero Hilos, Tiempo, Total: ${TEST_OUT}"
  sleep 5s
done
echo ""
echo -n "Por favor espere 20 segundos, para que se estabilize la pc "
sleep 20s
gnuplot -persist grafica.plt
