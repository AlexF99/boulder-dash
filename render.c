#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "rockford.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

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
        if (key >= '0' && key <= '3')
            return assets[5];
        else if (key >= '5' && key <= '8')
            return assets[6];
        
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

    length = snprintf( NULL, 0, "%d", mapa->diamonds);
    char* diamonds_to_open = malloc( length + 1 );
    snprintf( diamonds_to_open, length + 1, "%d", mapa->diamonds);
    
    length = snprintf( NULL, 0, "%d", mapa->points_per_diamond);
    char* points_per_diamond = malloc( length + 1 );
    snprintf( points_per_diamond, length + 1, "%d", mapa->points_per_diamond);
    
    length = snprintf( NULL, 0, "%d", mapa->time_left);
    char* time_left = malloc( length + 1 );
    snprintf( time_left, length + 1, "%d", mapa->time_left);
    
    length = snprintf( NULL, 0, "%d", rockford->points);
    char* points = malloc( length + 1 );
    snprintf( points, length + 1, "%d", rockford->points);


    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), 5, 5, 0, diamonds);
    al_draw_text(font, al_map_rgb(255, 255, 255), 23, 5, 0, "/");
    al_draw_text(font, al_map_rgb(255, 255, 255), 35, 5, 0, diamonds_to_open);

    al_draw_text(font, al_map_rgb(255, 255, 255), 100, 5, 0, "points per diamond: ");
    al_draw_text(font, al_map_rgb(255, 255, 255), 260, 5, 0, points_per_diamond);
    
    al_draw_text(font, al_map_rgb(255, 255, 255), 300, 5, 0, "points: ");
    al_draw_text(font, al_map_rgb(255, 255, 255), 360, 5, 0, points);
    
    al_draw_text(font, al_map_rgb(255, 255, 255), 560, 5, 0, time_left);


    for (int i = 0; i < mapa->linhas; i++)
    {
        for (j = 0; j < mapa->colunas; j++)
        {
            asset = get_asset(assets, mapa->game_mat[i][j]);
            if (asset)
                al_draw_bitmap(get_asset(assets, mapa->game_mat[i][j]), j * 16, (i * 16) + 16, 0);
        }
    }
    free(diamonds);
    free(diamonds_to_open);
    al_flip_display();
}