typedef struct t_map {
    int linhas, colunas;
    int diamonds;
    int points_per_diamond;
    int door;
    int time_left;
    char **game_mat;
} t_map;