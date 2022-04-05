#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include "map.h"
#include "rockford.h"
#include <allegro5/allegro_font.h>
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
    case 's': // exit
        return assets[7];

    default:
        return NULL;
    }

    return NULL;
}

void render(t_map *mapa, ALLEGRO_BITMAP **assets, t_rockford *rockford, ALLEGRO_FONT* font)
{
    int i, j;
    ALLEGRO_BITMAP *asset = NULL;

    int length = snprintf( NULL, 0, "%d", rockford->diamonds);
    char* diamonds = malloc( length + 1 );
    snprintf( diamonds, length + 1, "%d", rockford->diamonds);

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, diamonds);
    for (int i = 0; i < mapa->linhas; i++)
    {
        for (j = 0; j < mapa->colunas; j++)
        {
            asset = get_asset(assets, mapa->game_mat[i][j]);
            if (asset)
                al_draw_bitmap(get_asset(assets, mapa->game_mat[i][j]), j * 17, (i * 17) + 17, 0);
        }
    }
    free(diamonds);
    al_flip_display();
}