#include <allegro5/allegro.h>

#ifndef _RENDER_H_
#define _RENDER_H_

void show_txt(ALLEGRO_FONT* font, char *file_name);

ALLEGRO_BITMAP *get_asset(ALLEGRO_BITMAP **assets, char *key);

void render(t_map *mapa, ALLEGRO_BITMAP **assets, t_rockford *rockford, ALLEGRO_FONT* font, bool instructions, bool leaderboard);

#endif