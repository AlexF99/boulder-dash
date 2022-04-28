CFLAGS = -Wall -std=c99

allegro_deps = -lallegro -lallegro_font -lallegro_image -lallegro_audio -lallegro_acodec

common_o = level.o render.o moves.o records.o game.o

all:
	gcc ${CFLAGS} -c level.c -o level.o
	gcc ${CFLAGS} -c render.c -o render.o
	gcc ${CFLAGS} -c moves.c -o moves.o
	gcc ${CFLAGS} -c records.c -o records.o
	gcc ${CFLAGS} -c game.c -o game.o
	gcc ${CFLAGS} ${common_o} main.c ${allegro_deps} -o bdash

clean:
	-rm -f *~ *.o

purge:
	-rm -f bdash
	-rm -f records.txt