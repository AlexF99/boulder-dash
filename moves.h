#ifndef _MOVES_H_
#define _MOVES_H_

void move_rockford(t_map *mapa, t_rockford *rockford, char direction, int *done, int *next_level);

void gravity(char element, char base, t_map *mapa, t_rockford *rockford, int *done);

#endif