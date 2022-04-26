#include <stdio.h>
#include <stdlib.h>
#include "rockford.h"
#include "map.h"

void move_rockford(t_map *mapa, t_rockford *rockford, char direction, int *done, int *next_level)
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

    if (destino != '#' && destino != 'o' && destino != '-' && !(destino >= '0' && destino <= '3'))
    {
        if (destino == 's')
        {
            if (mapa->door)
                *next_level = 1;
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
        }
    }

    if (destino == 'o')
    {
        if (direction == 'l' && mapa->game_mat[rockford->y][rockford->x - 2] == ' ')
        {
            mapa->game_mat[rockford->y][rockford->x - 2] = 'o';
            mapa->game_mat[rockford->y][rockford->x] = ' ';
            rockford->x--;
        }
        else if (direction == 'r' && mapa->game_mat[rockford->y][rockford->x + 2] == ' ')
        {
            mapa->game_mat[rockford->y][rockford->x + 2] = 'o';
            mapa->game_mat[rockford->y][rockford->x] = ' ';
            rockford->x++;
        }
    }
    mapa->game_mat[rockford->y][rockford->x] = '@';
}

void gravity(char element, char base, t_map *mapa, t_rockford *rockford, int *done)
{
    int i, j;

    for (i = 0; i < mapa->linhas; i++)
    {
        for (j = 0; j < mapa->colunas; j++)
        {
            if (mapa->game_mat[i][j] != '#')
            {
                if (mapa->game_mat[i][j] == element)
                {
                    if (mapa->game_mat[i + 1][j] == ' ')
                        mapa->game_mat[i][j] = base;
                    else if (mapa->game_mat[i + 1][j] == 'o' || mapa->game_mat[i + 1][j] == '-')
                    {
                        if (mapa->game_mat[i][j + 1] == ' ' && mapa->game_mat[i + 1][j + 1] == ' ')
                        {
                            mapa->game_mat[i][j] = ' ';
                            mapa->game_mat[i][j + 1] = element;
                        }
                        else if (mapa->game_mat[i][j - 1] == ' ' && mapa->game_mat[i + 1][j - 1] == ' ')
                        {
                            mapa->game_mat[i][j] = ' ';
                            mapa->game_mat[i][j - 1] = element;
                        }
                    }
                }

                if (mapa->game_mat[i][j] >= base && mapa->game_mat[i][j] < base + 3)
                { // caindo
                    if (mapa->game_mat[i + 1][j] == ' ')
                        mapa->game_mat[i][j]++;
                    else if (mapa->game_mat[i + 1][j] == '.' ||
                             mapa->game_mat[i + 1][j] == 'o' ||
                             mapa->game_mat[i + 1][j] == '-' ||
                             mapa->game_mat[i + 1][j] == '#' ||
                             mapa->game_mat[i + 1][j] == 's' ||
                             mapa->game_mat[i + 1][j] == '*')
                        mapa->game_mat[i][j] = element;
                    else if (mapa->game_mat[i + 1][j] == '@') // rockford dies
                    {
                        rockford->alive = 0;
                        mapa->game_mat[rockford->y][rockford->x] = 'x';
                        mapa->game_mat[rockford->y+1][rockford->x] = 'x';
                        mapa->game_mat[rockford->y-1][rockford->x] = 'x';
                        mapa->game_mat[rockford->y][rockford->x+1] = 'x';
                        mapa->game_mat[rockford->y][rockford->x-1] = 'x';
                        mapa->game_mat[rockford->y+1][rockford->x+1] = 'x';
                        mapa->game_mat[rockford->y-1][rockford->x+1] = 'x';
                        mapa->game_mat[rockford->y+1][rockford->x-1] = 'x';
                        mapa->game_mat[rockford->y-1][rockford->x-1] = 'x';
                    }
                }
                if (mapa->game_mat[i][j] == (base + 3) && mapa->game_mat[i + 1][j] == ' ')
                {
                    mapa->game_mat[i + 1][j] = (base + 1);
                    mapa->game_mat[i][j] = ' ';
                }
            }
        }
    }
}

void diamond_easter_egg(t_map *mapa) {
    int i, j;
    for (i = 0; i < mapa->linhas; i++)
    {
        for (j = 0; j < mapa->colunas; j++)
        {
            if (mapa->game_mat[i][j] == 'o')
            {
                mapa->game_mat[i][j] = '*';
                return;
            }
        }
    }
}