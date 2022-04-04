#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include "map.h"

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
        return NULL;
    }

    return NULL;
}

void render(t_map *mapa, ALLEGRO_BITMAP **assets)
{
    int i, j;
    ALLEGRO_BITMAP *asset = NULL;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (int i = 0; i < mapa->linhas; i++)
    {
        for (j = 0; j < mapa->colunas; j++)
        {
            asset = get_asset(assets, mapa->game_mat[i][j]);
            if (asset)
                al_draw_bitmap(get_asset(assets, mapa->game_mat[i][j]), j * 17, i * 17, 0);
        }
    }
    al_flip_display();
}