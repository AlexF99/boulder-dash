#include "rockford.h"
#include "map.h"

void move_rockford(t_map *mapa, t_rockford *rockford, char direction, int *done)
{
    char destino;

    switch (direction)
    {
    case 'u':
        destino = mapa->game_mat[rockford->y - 1][rockford->x];
        break;
    case 'd':
        destino = mapa->game_mat[rockford->y + 1][rockford->x];
        break;
    case 'l':
        destino = mapa->game_mat[rockford->y][rockford->x - 1];
        break;
    case 'r':
        destino = mapa->game_mat[rockford->y][rockford->x + 1];
        break;
    
    default:
        destino = ' ';
        break;
    }

    if (destino != '#' && destino != 'o')
    {
        if (destino == 's')
        {
            if (mapa->door)
                *done = 1;
        }
        else
        {
            if (destino == '*')
            {
                rockford->diamonds++;
                rockford->points += mapa->points_per_diamond;
            }
            mapa->game_mat[rockford->y][rockford->x] = ' ';
            switch (direction)
            {
            case 'u':
                rockford->y--;
                break;
            case 'd':
                rockford->y++;
                break;
            case 'l':
                rockford->x--;
                break;
            case 'r':
                rockford->x++;
                break;
            default:
                break;
            }
            mapa->game_mat[rockford->y][rockford->x] = '@';
        }
    }
    return;
}