
allegro_deps = -lallegro -lallegro_font -lallegro_image -lallegro_audio -lallegro_acodec

common_o = level.o render.o moves.o records.o game.o

all:
	gcc -c level.c -o level.o
	gcc -c render.c -o render.o
	gcc -c moves.c -o moves.o
	gcc -c records.c -o records.o
	gcc -c game.c -o game.o
	gcc -Wall ${common_o} main.c ${allegro_deps} -o bdash

clean:
	-rm -f *~ *.o

purge:
	-rm -f bdash
	-rm -f records.txt