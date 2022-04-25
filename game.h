#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#ifndef _GAME_H_
#define _GAME_H_

#define d_height 1280
#define d_width 720

typedef struct t_allegro_vars {
    ALLEGRO_TIMER *timer;
    ALLEGRO_TIMER *tick;
    ALLEGRO_TIMER *time_limit;

    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_FONT *font;

    ALLEGRO_BITMAP **assets;
} t_allegro_vars;

void must_init(bool test, const char *description);

t_allegro_vars *vars_init();

void game_main_loop(t_allegro_vars *allegro_vars);

void vars_destroy(t_allegro_vars *allegro_vars);

#endif