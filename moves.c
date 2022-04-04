#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "rockford.h"

int destino_valido(char direction, t_map **mapa, t_rockford **rockford) {

    char destino;

    // verifica destino
    switch (direction)
    {
    case 'u':
        destino = (*mapa)->game_mat[(*rockford)->y - 1][(*rockford)->x];
    case 'd':
        destino = (*mapa)->game_mat[(*rockford)->y + 1][(*rockford)->x];
    case 'l':
        destino = (*mapa)->game_mat[(*rockford)->y][(*rockford)->x - 1];
    case 'r':
        destino = (*mapa)->game_mat[(*rockford)->y][(*rockford)->x + 1];

    default:
        destino = ' ';
    }

    printf("destino: %c\n direcao: %c", destino, direction);

    if (destino == '#') return 0;

    return 1;
}

void move_rockford(char direction, t_map **mapa, t_rockford **rockford) {

    if (!destino_valido(direction, mapa, rockford)) return;

    // move
    switch (direction)
    {
    case 'u':
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = ' ';
        (*rockford)->y--;
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = '@';
    case 'd':
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = ' ';
        (*rockford)->y++;
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = '@';
    case 'l':
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = ' ';
        (*rockford)->x--;
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = '@';
    case 'r':
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = ' ';
        (*rockford)->x++;
        (*mapa)->game_mat[(*rockford)->y][(*rockford)->x] = '@';

    default:
        return;
    }

}