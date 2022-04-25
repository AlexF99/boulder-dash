#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "map.h"
#include "rockford.h"
#include "level.h"
#include "render.h"
#include "moves.h"
#include "records.h"

#define KEY_SEEN 1
#define KEY_RELEASED 2

void must_init(bool test, const char *description)
{
    if (test)
        return;

    fprintf(stderr, "couldn't initialize %s\n", description);
    exit(1);
}

t_allegro_vars *vars_init()
{

    t_allegro_vars *allegro_vars = malloc(sizeof(t_allegro_vars));

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    allegro_vars->timer = al_create_timer(1.0 / 60.0);
    must_init(allegro_vars->timer, "timer");

    allegro_vars->tick = al_create_timer(1.0 / 10.0);
    must_init(allegro_vars->tick, "tick");

    allegro_vars->time_limit = al_create_timer(1.0 / 1.0);
    must_init(allegro_vars->time_limit, "time_limit");

    allegro_vars->queue = al_create_event_queue();
    must_init(allegro_vars->queue, "queue");

    allegro_vars->disp = al_create_display(d_height, d_width);
    must_init(allegro_vars->disp, "display");

    allegro_vars->font = al_create_builtin_font();
    must_init(allegro_vars->font, "font");

    must_init(al_init_image_addon(), "image addon");

    // carrega assets
    allegro_vars->assets = malloc(9 * sizeof(ALLEGRO_BITMAP *));

    allegro_vars->assets[0] = al_load_bitmap("./assets/rockford.png");
    must_init(allegro_vars->assets[0], "rockford");
    allegro_vars->assets[1] = al_load_bitmap("./assets/wall.png");
    must_init(allegro_vars->assets[1], "wall");
    allegro_vars->assets[2] = al_load_bitmap("./assets/magic.png");
    must_init(allegro_vars->assets[2], "magic");
    allegro_vars->assets[3] = al_load_bitmap("./assets/steel.png");
    must_init(allegro_vars->assets[3], "steel");
    allegro_vars->assets[4] = al_load_bitmap("./assets/dirt.png");
    must_init(allegro_vars->assets[4], "dirt");
    allegro_vars->assets[5] = al_load_bitmap("./assets/boulder.png");
    must_init(allegro_vars->assets[5], "boulder");
    allegro_vars->assets[6] = al_load_bitmap("./assets/diamond.png");
    must_init(allegro_vars->assets[6], "diamond");
    allegro_vars->assets[7] = al_load_bitmap("./assets/firefly.png");
    must_init(allegro_vars->assets[7], "firefly");
    allegro_vars->assets[8] = al_load_bitmap("./assets/exit.png");
    must_init(allegro_vars->assets[8], "exit");

    al_register_event_source(allegro_vars->queue, al_get_keyboard_event_source());
    al_register_event_source(allegro_vars->queue, al_get_display_event_source(allegro_vars->disp));
    al_register_event_source(allegro_vars->queue, al_get_timer_event_source(allegro_vars->timer));
    al_register_event_source(allegro_vars->queue, al_get_timer_event_source(allegro_vars->tick));
    al_register_event_source(allegro_vars->queue, al_get_timer_event_source(allegro_vars->time_limit));

    return allegro_vars;
}

void game_main_loop(t_allegro_vars *allegro_vars)
{

    int done = 0;
    int next_level = 0;
    bool redraw = true;
    bool instructions = false;
    bool leaderboard = false;
    t_rockford *rockford = NULL;
    t_map *mapa = NULL;

    char level[19] = "./levels/mapa0.txt";

    mapa = le_nivel(level, &rockford, next_level);

    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(allegro_vars->timer);
    al_start_timer(allegro_vars->tick);
    al_start_timer(allegro_vars->time_limit);

    while (1)
    {
        al_wait_for_event(allegro_vars->queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (event.timer.source == allegro_vars->time_limit)
            {
                if (mapa->time_left > 0)
                    mapa->time_left--;
                else
                    rockford->alive = 0;
            }

            if (event.timer.source == allegro_vars->tick)
            {
                if (key[ALLEGRO_KEY_H] || key[ALLEGRO_KEY_F1])
                    instructions = !instructions;

                if (key[ALLEGRO_KEY_UP])
                    move_rockford(mapa, rockford, 'u', &done, &next_level);
                else if (key[ALLEGRO_KEY_DOWN])
                    move_rockford(mapa, rockford, 'd', &done, &next_level);
                else if (key[ALLEGRO_KEY_LEFT])
                    move_rockford(mapa, rockford, 'l', &done, &next_level);
                else if (key[ALLEGRO_KEY_RIGHT])
                    move_rockford(mapa, rockford, 'r', &done, &next_level);
                else if (key[ALLEGRO_KEY_PGUP])
                {
                    if (level[13] > '0')
                    {
                        level[13]--;
                        mapa = le_nivel(level, &rockford, next_level);
                    }
                }
                else if (key[ALLEGRO_KEY_PGDN])
                {
                    if (level[13] < '9')
                    {
                        level[13]++;
                        mapa = le_nivel(level, &rockford, next_level);
                    }
                }
                else if (key[ALLEGRO_KEY_ESCAPE])
                    done = 1;

                if (mapa->diamonds == rockford->diamonds)
                    mapa->door = 1;

                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                gravity('o', '0', mapa, rockford, &done);
                gravity('*', '5', mapa, rockford, &done);
            }

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = 1;
            break;
        }

        if (next_level)
        {
            if (level[13] < '9')
            {
                level[13]++;
                mapa = le_nivel(level, &rockford, next_level);
                next_level = 0;
            }
            else
            {
                // zerou o jogo
                save_records(rockford->points);
                leaderboard = true;
            }
        }

        if (done)
            break;

        if (!rockford->alive)
        {
            save_records(rockford->points);
            leaderboard = true;
        }

        if (redraw && al_is_event_queue_empty(allegro_vars->queue))
        {
            render(mapa, allegro_vars->assets, rockford, allegro_vars->font, instructions, leaderboard);
            redraw = false;
        }
    }
}

void vars_destroy(t_allegro_vars *allegro_vars)
{
    for (int i = 0; i < 9; i++)
        al_destroy_bitmap(allegro_vars->assets[i]);
    free(allegro_vars->assets);
    al_destroy_font(allegro_vars->font);
    al_destroy_display(allegro_vars->disp);
    al_destroy_timer(allegro_vars->timer);
    al_destroy_timer(allegro_vars->tick);
    al_destroy_event_queue(allegro_vars->queue);
}