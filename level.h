#ifndef _LEVEL_H_
#define _LEVEL_H_

char **aloca_matriz(int linhas, int colunas);

t_map *le_nivel(char *nome_arquivo, t_rockford **rockford, int next_level);

#endif