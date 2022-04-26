#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#ifndef _MOVES_H_
#define _MOVES_H_

void move_rockford(t_map *mapa, t_rockford *rockford, char direction, int *next_level, ALLEGRO_SAMPLE **sounds);

void gravity(char element, char base, t_map *mapa, t_rockford *rockford);

void diamond_easter_egg(t_map *mapa);

#endif