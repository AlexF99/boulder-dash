#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

enum
{
    INICIO,
    SERVINDO,
    JOGANDO,
    FIMPART,
    FIMJOGO
} state;

int main()
{
    static ALLEGRO_DISPLAY *display1 = NULL;

    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar allegro\n");
        return -1;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao instalar teclado allegro\n");
        return -1;
    }

    display1 = al_create_display(320, 200);

    while (1) {}
    return 0;
}