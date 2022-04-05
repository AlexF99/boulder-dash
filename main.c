#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "map.h"
#include "rockford.h"
#include "level.h"
#include "render.h"

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main()
{
    int d_height = 800;
    int d_width = 480;
    int done = 0;
    t_rockford *rockford = NULL;
    t_map *mapa = NULL;

    ALLEGRO_BITMAP **assets;

    assets = malloc(8 * sizeof(ALLEGRO_BITMAP *));

    mapa = le_nivel("mapa1.txt", &rockford);

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

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

    bool redraw = true;
    ALLEGRO_EVENT event;

    #define KEY_SEEN 1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);

    char destino;

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_UP])
            {
                destino = mapa->game_mat[rockford->y - 1][rockford->x];
                if (destino != '#' && destino != 'o')
                {
                    if (destino == 's') {
                        if (mapa->door)
                            done = true;
                    } else {
                        if (destino == '*')
                            rockford->diamonds++;
                        mapa->game_mat[rockford->y][rockford->x] = ' ';
                        rockford->y--;
                        mapa->game_mat[rockford->y][rockford->x] = '@';
                    }
                }
            }
            if (key[ALLEGRO_KEY_DOWN])
            {
                destino = mapa->game_mat[rockford->y + 1][rockford->x];
                if (destino != '#' && destino != 'o')
                {
                    if (destino == 's') {
                        if (mapa->door)
                            done = true;
                    } else {
                        if (destino == '*')
                            rockford->diamonds++;
                        mapa->game_mat[rockford->y][rockford->x] = ' ';
                        rockford->y++;
                        mapa->game_mat[rockford->y][rockford->x] = '@';
                    }
                }
            }
            if (key[ALLEGRO_KEY_LEFT])
            {
                destino = mapa->game_mat[rockford->y][rockford->x - 1];
                if (destino != '#' && destino != 'o')
                {
                    if (destino == 's') {
                        if (mapa->door)
                            done = true;
                    } else {
                        if (destino == '*')
                            rockford->diamonds++;
                        mapa->game_mat[rockford->y][rockford->x] = ' ';
                        rockford->x--;
                        mapa->game_mat[rockford->y][rockford->x] = '@';
                    }
                }
            }
            if (key[ALLEGRO_KEY_RIGHT])
            {
                destino = mapa->game_mat[rockford->y][rockford->x + 1];
                if (destino != '#' && destino != 'o')
                {
                    if (destino == 's') {
                        if (mapa->door)
                            done = true;
                    } else {
                        if (destino == '*')
                            rockford->diamonds++;
                        mapa->game_mat[rockford->y][rockford->x] = ' ';
                        rockford->x++;
                        mapa->game_mat[rockford->y][rockford->x] = '@';
                    }
                }
            }

            if (mapa->diamonds == rockford->diamonds) mapa->door = 1;

            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
        if (done)
            break;

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
    al_destroy_event_queue(queue);

    return 0;
}