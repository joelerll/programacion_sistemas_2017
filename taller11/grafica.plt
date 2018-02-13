set xlabel "Hilos"
set ylabel "Tiempo"
set title "Grafica Hilos vs Tiempo"
plot 'datosHvsT.dat' using 1:2 with lines
