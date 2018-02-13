RUTA=$1
TEXTO=$2
RED='\033[0;36m'
NC='\033[0m'
if [ -d CARPETA ]; then
  echo "La carpeta existe"
else
  echo "La carpeta no existe"
fi
for file in  `ls $RUTA/Pagina* | sort`
do
    COMANDO=$(cat $file | grep $TEXTO)
    if [ -n "$COMANDO" ]; then
      echo "\n \n"
      echo  " ${RED} ${file} ${NC}"
      echo "\n \n"
      grep $TEXTO $file --color=auto
    fi
done
