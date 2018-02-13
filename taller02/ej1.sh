RUTA_LIBRO="$1/libro.txt"
CARPETA=$2
N=$3

if [ -d CARPETA ]; then
  echo "La carpeta ya existe"
  rm -r $CARPETA
else
  echo "Creando carpeta $CARPETA"
  mkdir -p $CARPETA
fi

split -l $N $RUTA_LIBRO
mv x* $CARPETA
CONT=1

for file in  `ls $CARPETA/x* | sort`
do
    if [ $CONT -lt 10 ]; then
      mv $file $CARPETA/Pagina00$CONT
    elif [ $CONT -lt 100 ]; then
      mv $file $CARPETA/Pagina0$CONT
    else
      mv $file $CARPETA/Pagina$CONT
    fi
    CONT=$(($CONT+1))
done
