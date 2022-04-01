#include <allegro5/allegro.h>

ALLEGRO_BITMAP *get_asset(ALLEGRO_BITMAP **assets, char *key);

void render(int d_height, int d_width, char **game_mat, ALLEGRO_BITMAP **assets);