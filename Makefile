all:
	gcc -c level.c -o level.o
	gcc -c render.c -o render.o
	gcc -c moves.c -o moves.o
	gcc -c records.c -o records.o
	gcc -c allegro_vars.c -lallegro -lallegro_font -lallegro_image -o allegro_vars.o
	gcc -Wall level.o render.o moves.o records.o allegro_vars.o main.c -o bdash

clean:
	-rm -f *~ *.o

purge:
	-rm -f bdash