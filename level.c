#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char **le_nivel(char *nome_arquivo)
{
    FILE *nivel_txt = NULL;
    int i, j;
    int linhas, colunas;
    char **game_mat = NULL;
    char *new_char;

    nivel_txt = fopen(nome_arquivo, "r");
    if (!nivel_txt)
    {
        fprintf(stderr, "erro ao abrir arquivo");
        exit(1);
    }

    fscanf(nivel_txt, "%d", &linhas);
    fscanf(nivel_txt, "%d", &colunas);

    game_mat = aloca_matriz(linhas, colunas);
    new_char = malloc(colunas * sizeof(char));

    // for (i = 0; i < linhas; i++)
    // {
    //     for (j = 0; j < colunas; j++)
    //     {
    //         new_char = fgetc(nivel_txt);
    //         // putchar(new_char);
    //         if (new_char != '\n')
    //             game_mat[i][j] = new_char;
    //     }
    // }

    for (i = 0; i < linhas; i++)
    {
        // fscanf(nivel_txt, "%s", game_mat[i]);
        fgets(new_char, colunas + 1, nivel_txt);
        if (strcmp(new_char, "\n") && strcmp(new_char, ""))
            strcpy(game_mat[i], new_char);
    }

    // for (i = 0; i < linhas; i++)
    // {
    //     printf("\n%d: ", i);
    //     for (j = 0; j < colunas; j++)
    //     {
    //         putchar(game_mat[i][j]);
    //     }
    //     // printf("\n");
    // }

    fclose(nivel_txt);

    return game_mat;
}