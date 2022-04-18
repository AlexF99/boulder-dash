#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

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

int main()
{
    int d_height = 800;
    int d_width = 480;
    int done = 0;
    t_rockford *rockford = NULL;
    t_map *mapa = NULL;

    char level[19] = "./levels/mapa1.txt";

    ALLEGRO_BITMAP **assets;

    assets = malloc(8 * sizeof(ALLEGRO_BITMAP *));

    mapa = le_nivel("./levels/mapa1.txt", &rockford);

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_TIMER *tick = al_create_timer(1.0 / 10.0);
    must_init(tick, "tick");

    ALLEGRO_TIMER *time_limit = al_create_timer(1.0 / 1.0);
    must_init(time_limit, "time_limit");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY *disp = al_create_display(d_height, d_width);
    must_init(disp, "display");

    ALLEGRO_FONT *font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");

    // carrega assets
    assets[0] = al_load_bitmap("./assets/rockford.png");
    must_init(assets[0], "rockford");
    assets[1] = al_load_bitmap("./assets/wall.png");
    must_init(assets[1], "wall");
    assets[2] = al_load_bitmap("./assets/magic.png");
    must_init(assets[2], "magic");
    assets[3] = al_load_bitmap("./assets/steel.png");
    must_init(assets[3], "steel");
    assets[4] = al_load_bitmap("./assets/dirt.png");
    must_init(assets[4], "dirt");
    assets[5] = al_load_bitmap("./assets/boulder.png");
    must_init(assets[5], "boulder");
    assets[6] = al_load_bitmap("./assets/diamond.png");
    must_init(assets[6], "diamond");
    assets[7] = al_load_bitmap("./assets/exit.png");
    must_init(assets[7], "exit");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(tick));
    al_register_event_source(queue, al_get_timer_event_source(time_limit));

    bool redraw = true;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    al_start_timer(tick);
    al_start_timer(time_limit);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (event.timer.source == time_limit)
            {
                if (mapa->time_left > 0)
                    mapa->time_left--;
                else
                    done = 1;
            }

            if (event.timer.source == tick)
            {
                if (key[ALLEGRO_KEY_UP])
                    move_rockford(mapa, rockford, 'u', &done);
                else if (key[ALLEGRO_KEY_DOWN])
                    move_rockford(mapa, rockford, 'd', &done);
                else if (key[ALLEGRO_KEY_LEFT])
                    move_rockford(mapa, rockford, 'l', &done);
                else if (key[ALLEGRO_KEY_RIGHT])
                    move_rockford(mapa, rockford, 'r', &done);
                else if (key[ALLEGRO_KEY_PGUP])
                {
                    if (level[13] > '1')
                    {
                        level[13]--;
                        mapa = le_nivel(level, &rockford);
                    }
                }
                else if (key[ALLEGRO_KEY_PGDN])
                {
                    if (level[13] < '2')
                    {
                        level[13]++;
                        mapa = le_nivel(level, &rockford);
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
        if (done) {
            save_records("rockford", rockford->points);
            break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            render(mapa, assets, rockford, font);
            redraw = false;
        }
    }

    for (int i = 0; i < 8; i++)
        al_destroy_bitmap(assets[i]);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_timer(tick);
    al_destroy_event_queue(queue);

    return 0;
}