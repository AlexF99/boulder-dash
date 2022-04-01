#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

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
    int d_height = 640;
    int d_width = 480;
    char **game_mat = NULL;

    ALLEGRO_BITMAP **assets;

    assets = malloc(7 * sizeof(ALLEGRO_BITMAP *));

    game_mat = le_nivel("mapa2.txt");

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
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

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            render(d_height, d_width, game_mat, assets);
            // al_clear_to_color(al_map_rgb(0, 0, 0));
            // for (int i = 0; i < d_height; i += 15)
            //     al_draw_bitmap(steel, i, 20, 0);

            // for (int i = 0; i < d_height; i += 15)
            //     al_draw_bitmap(steel, i, 450, 0);

            // for (int i = 35; i < d_width - 20; i += 15)
            //     al_draw_bitmap(steel, 0, i, 0);

            // al_draw_bitmap(assets[0], 20, 40, 0);
            al_flip_display();

            redraw = false;
        }
    }

    for (int i = 0; i < 7; i++)
        al_destroy_bitmap(assets[i]);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}