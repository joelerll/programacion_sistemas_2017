OBJS = mostrar_nombre.o calcular_bmi.o calcular_agua_corporal.o calcular_tasa_metabolica.o calcular_ritmo_car_res.o
CCC = mostrar_nombre.c calcular_bmi.c calcular_agua_corporal.c calcular_tasa_metabolica.c calcular_ritmo_car_res.c
all: todo
mostrar_nombre.o: datos.h
	gcc -c mostrar_nombre.c

calcular_bmi.o: datos.h
	gcc -c calcular_bmi.c

calcular_agua_corporal.o: datos.h
	gcc -c calcular_agua_corporal.c

calcular_tasa_metabolica.o: datos.h
	gcc -c calcular_tasa_metabolica.c

calcular_ritmo_car_res.o: datos.h
	gcc -c calcular_ritmo_car_res.c

todo: ${OBJS}
	gcc  -Wall ${OBJS} main.c -o a.salida

estatico:
	gcc -L./ main.o -ldatos -lm -o dinamico

dinamico:
	gcc main.o libdatos.a -lm -o estatico

libreria: a.salida
	ar rcs libdatos.a a.salida

parte4:
	gcc datos.h -shared -fPIC ${CCC} main.c -o libdatos.so

clean:
	rm *.o a.salida *.a *.so
