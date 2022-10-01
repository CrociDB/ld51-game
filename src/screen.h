#ifndef _SHAKE_H_
#define _SHAKE_H_

typedef struct 
{
    int shake_time;
    int shake_strength;

    unsigned int game_frame;
} screen_t;

screen_t* screen_create();
void screen_destroy(screen_t* screen);

void screen_update(screen_t* screen);
void screen_render(screen_t* screen);

void screen_shake(screen_t* screen, int time, int strength);

#endif
