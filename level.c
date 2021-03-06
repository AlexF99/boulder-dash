#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "rockford.h"

char **aloca_matriz(int linhas, int colunas)
{
    int i;
    char **mat = NULL;

    mat = malloc(linhas * sizeof(char *) + linhas * colunas * sizeof(char));
    if (mat == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }
    mat[0] = (char *)(mat + linhas);
    for (i = 1; i < linhas; i++)
        mat[i] = mat[0] + (i * colunas);

    return mat;
}

t_map *le_nivel(char *nome_arquivo, t_rockford **rockford, int next_level)
{
    t_map *mapa = NULL;
    FILE *nivel_txt = NULL;
    int i, j;

    nivel_txt = fopen(nome_arquivo, "r");
    if (!nivel_txt)
    {
        fprintf(stderr, "erro ao abrir arquivo %s\n", nome_arquivo);
        exit(1);
    }

    mapa = malloc(sizeof(t_map));
    if (mapa == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }
    mapa->door = 0;

    if (!next_level)
    {
        *rockford = malloc(sizeof(t_rockford));
        if (*rockford == NULL)
        {
            fprintf(stderr, "erro de malloc");
            exit(1);
        }
        (*rockford)->alive = 1;
        (*rockford)->points = 0;
    }
    (*rockford)->diamonds = 0;

    fscanf(nivel_txt, "%d %d\n%d %d\n%d\n", &mapa->linhas, &mapa->colunas, &mapa->diamonds, &mapa->points_per_diamond, &mapa->time_left);

    mapa->game_mat = aloca_matriz(mapa->linhas, mapa->colunas);

    for (i = 0; i < mapa->linhas; i++)
    {
        for (j = 0; j < mapa->colunas; j++)
        {
            fscanf(nivel_txt, "%c", &mapa->game_mat[i][j]);
            if (mapa->game_mat[i][j] == '@')
            {
                (*rockford)->y = i;
                (*rockford)->x = j;
            }
        }
        fscanf(nivel_txt, "\n");
    }

    fclose(nivel_txt);

    return mapa;
}