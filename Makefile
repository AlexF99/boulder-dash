all:
	gcc -c level.c -o level.o
	gcc -c render.c -o render.o
	gcc -c moves.c -o moves.o
	gcc -Wall level.o render.o moves.o main.c -lallegro -lallegro_font -lallegro_image -o bdash