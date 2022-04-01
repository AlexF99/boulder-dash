#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_image.h>

ALLEGRO_BITMAP *get_asset(ALLEGRO_BITMAP **assets, char key)
{

    switch (key)
    {
    case '@': // rockford
        return assets[0];
    case '#': // wall
        return assets[1];
    case '.': // dirt
        return assets[4];
    case 'o': // boulder
        return assets[5];
    case '*': // diamond
        return assets[6];

    default:
        return assets[4];
    }

    return assets[4];
}

void render(int d_height, int d_width, char **game_mat, ALLEGRO_BITMAP **assets)
{
    int i, j;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (int i = 0; i < d_height; i += 15)
    {
        for (j = 0; j < d_width; j += 15)
        {
            al_draw_bitmap(get_asset(assets, game_mat[i][j]), i, 20, 0);
        }
    }

    al_flip_display();
}