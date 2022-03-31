all:
	gcc -c level.c -o level.o
	gcc -Wall level.o main.c -lallegro -lallegro_font -lallegro_image -o bdash