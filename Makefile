all:
	gcc -c level.c -o level.o
	gcc -c render.c -o render.o
	gcc -Wall level.o render.o main.c -lallegro -lallegro_font -lallegro_image -o bdash