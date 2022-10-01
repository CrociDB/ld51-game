#include "screen.h"
#include "wasm4.h"
#include "defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

screen_t* screen_create()
{
    screen_t* screen = (screen_t*)malloc(sizeof(screen_t));
    screen->shake_time = screen->shake_strength = 0;
    return screen;
}

void screen_destroy(screen_t* screen)
{
    free(screen);
}

void screen_update(screen_t* screen)
{
    screen->shake_time--;
    screen->game_frame++;
}

void screen_render(screen_t* screen)
{
    if (screen->shake_time <= 0) return;

    int x = (int)(frandom() * (float)screen->shake_strength) - (screen->shake_strength/2);

    if (x > 0)
    {
        for (int i = 0; i < SCREEN_SIZE; i++)
        {
            for (int j = 0; j < SCREEN_SIZE - x; j++)
            {
                int idx = (i * SCREEN_SIZE + j) >> 2;
                int copy = (i * SCREEN_SIZE + (j + x)) >> 2;

                FRAMEBUFFER[idx] = FRAMEBUFFER[copy];
            }
        }
    }
    else if (x < 0)
    {
        for (int i = SCREEN_SIZE; i >= 0; i--)
        {
            for (int j = SCREEN_SIZE; j >= -x ; j--)
            {
                int idx = (i * SCREEN_SIZE + j) >> 2;
                int copy = (i * SCREEN_SIZE + (j + x)) >> 2;

                FRAMEBUFFER[idx] = FRAMEBUFFER[copy];
            }
        }
    }

    int y = (int)(frandom() * (float)screen->shake_strength) - (screen->shake_strength/2);

    if (y > 0)
    {
        for (int i = 0; i < SCREEN_SIZE - y; i++)
        {
            for (int j = 0; j < SCREEN_SIZE; j++)
            {
                int idx = (i * SCREEN_SIZE + j) >> 2;
                int copy = ((i + y) * SCREEN_SIZE + j) >> 2;

                FRAMEBUFFER[idx] = FRAMEBUFFER[copy];
            }
        }
    }
    else if (y < 0)
    {
        for (int i = SCREEN_SIZE; i >= -y ; i--)
        {
            for (int j = SCREEN_SIZE; j >= 0 ; j--)
            {
                int idx = (i * SCREEN_SIZE + j) >> 2;
                int copy = ((i + y) * SCREEN_SIZE + j) >> 2;

                FRAMEBUFFER[idx] = FRAMEBUFFER[copy];
            }
        }
    }
}

void screen_shake(screen_t* screen, int time, int strength)
{
    screen->shake_time = time;
    screen->shake_strength = strength;
}

