all:
	gcc -c level.c -o level.o
	gcc -c render.c -o render.o
	gcc -c moves.c -o moves.o
	gcc -c records.c -o records.o
	gcc -c game.c -o game.o
	gcc -Wall level.o render.o moves.o records.o game.o main.c -lallegro -lallegro_font -lallegro_image -o bdash

clean:
	-rm -f *~ *.o

purge:
	-rm -f bdash
	-rm -f records.txt