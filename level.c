#include <stdio.h>
#include <stdlib.h>

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

void le_nivel(char *nome_arquivo)
{
    FILE *nivel_txt = NULL;
    int i, j;
    int linhas, colunas;
    char **game_mat = NULL;

    nivel_txt = fopen(nome_arquivo, "r");
    if (!nivel_txt)
    {
        fprintf(stderr, "erro ao abrir arquivo");
        exit(1);
    }

    fscanf(nivel_txt, "%d", &linhas);
    fscanf(nivel_txt, "%d", &colunas);

    game_mat = aloca_matriz(linhas, colunas);

    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            game_mat[i][j] = fgetc(nivel_txt);

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++)
            printf("%c", game_mat[i][j]);
        printf("newline\n\n");
    }
    
}