#ifndef _SHAKE_H_
#define _SHAKE_H_

typedef struct 
{
    unsigned int current_palette;

    int shake_time;
    int shake_strength;

    unsigned int game_frame;
} screen_t;

screen_t* screen_create();
void screen_destroy(screen_t* screen);

void screen_update(screen_t* screen);
void screen_render(screen_t* screen);

void screen_shake(screen_t* screen, int time, int strength);

void screen_set_palette(screen_t* screen, unsigned int p);
void screen_set_palette_game_next(screen_t* screen);
void screen_set_palette_random(screen_t* screen);

#endif
