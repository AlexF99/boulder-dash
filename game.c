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

#define NUM_ASSETS 9
#define NUM_SOUNDS 3

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

    if (allegro_vars == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }

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

    // init sons
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    allegro_vars->sounds = malloc(NUM_SOUNDS * sizeof(ALLEGRO_SAMPLE *));

    if (allegro_vars->sounds == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }

    allegro_vars->sounds[0] = al_load_sample("./assets/zdiamond.wav");
    must_init(allegro_vars->sounds[0], "zdiamond");
    allegro_vars->sounds[1] = al_load_sample("./assets/zlevel.wav");
    must_init(allegro_vars->sounds[1], "zlevel");
    allegro_vars->sounds[2] = al_load_sample("./assets/zover1.wav");
    must_init(allegro_vars->sounds[2], "zover");

    // carrega assets
    allegro_vars->assets = malloc(NUM_ASSETS * sizeof(ALLEGRO_BITMAP *));

    if (allegro_vars->assets == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }

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
    int time_ee = 0;
    int diamond_ee = 0;
    int done = 0;
    int next_level = 0;
    bool redraw = true;
    int game_over = 0;
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

                if (key[ALLEGRO_KEY_T] && time_ee < 5) // easter egg
                    time_ee++;
                if (time_ee >= 5)
                {
                    mapa->time_left += 20;
                    time_ee = 0;
                }
                if (key[ALLEGRO_KEY_R] && diamond_ee < 5) // easter egg
                    diamond_ee++;
                if (diamond_ee >= 5)
                {
                    diamond_easter_egg(mapa);
                    diamond_ee = 0;
                }
            }

            if (event.timer.source == allegro_vars->tick)
            {
                if (rockford->alive)
                {
                    if (key[ALLEGRO_KEY_UP])
                        move_rockford(mapa, rockford, 'u', &next_level, allegro_vars->sounds);
                    else if (key[ALLEGRO_KEY_DOWN])
                        move_rockford(mapa, rockford, 'd', &next_level, allegro_vars->sounds);
                    else if (key[ALLEGRO_KEY_LEFT])
                        move_rockford(mapa, rockford, 'l', &next_level, allegro_vars->sounds);
                    else if (key[ALLEGRO_KEY_RIGHT])
                        move_rockford(mapa, rockford, 'r', &next_level, allegro_vars->sounds);
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
                    if (mapa->diamonds == rockford->diamonds)
                        mapa->door = 1;

                    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                        key[i] &= KEY_SEEN;

                    gravity('o', '0', mapa, rockford);
                    gravity('*', '5', mapa, rockford);
                }
                else
                {
                    if (key[ALLEGRO_KEY_ENTER])
                    {
                        game_over = 0;
                        leaderboard = false;
                        mapa = le_nivel(level, &rockford, next_level);
                    }
                }

                if (key[ALLEGRO_KEY_ESCAPE])
                    done = 1;

                if (key[ALLEGRO_KEY_H] || key[ALLEGRO_KEY_F1])
                    instructions = !instructions;

                if (!rockford->alive && game_over < 10)
                {
                    al_play_sample(allegro_vars->sounds[2], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    
                    if (game_over == 0)
                        save_records(rockford->points);
                    game_over++;
                    if (game_over == 9)
                        leaderboard = true;
                }
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
            else if (game_over < 10)
            {
                if (game_over == 0)
                    save_records(rockford->points);
                game_over++;
                if (game_over == 9)
                    leaderboard = true;
            }
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(allegro_vars->queue))
        {
            render(mapa, allegro_vars->assets, rockford, allegro_vars->font, instructions, leaderboard);
            redraw = false;
        }
    }
}

void vars_destroy(t_allegro_vars *allegro_vars)
{
    for (int i = 0; i < NUM_ASSETS; i++)
        al_destroy_bitmap(allegro_vars->assets[i]);

    for (int i = 0; i < NUM_SOUNDS; i++)
        al_destroy_sample(allegro_vars->sounds[i]);

    free(allegro_vars->assets);
    al_destroy_font(allegro_vars->font);
    al_destroy_display(allegro_vars->disp);
    al_destroy_timer(allegro_vars->timer);
    al_destroy_timer(allegro_vars->tick);
    al_destroy_event_queue(allegro_vars->queue);
}