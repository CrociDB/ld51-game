#include "screen.h"
#include "wasm4.h"
#include "defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const unsigned int SCREEN_PALETTES[] = {
    0x48376c, 0x6c56ab, 0xb883b9, 0xbfdce1,
    0xfff6d3, 0xf9a875, 0xeb6b6f, 0x7c3f58,
    0x332c50, 0x46878f, 0x94e344, 0xe2f3e4,
    0x0f0f1b, 0x565a75, 0xc6b7be, 0xfafbf6,
    0xeff9d6, 0xba5044, 0x7a1c4b, 0x1b0326,
    0xd0d058, 0xa0a840, 0x708028, 0x405010,
    0xf8e3c4, 0xcc3495, 0x6b1fb1, 0x0b0630,
    0x46425e, 0x5b768d, 0xd17c7c, 0xf6c6a8,
    0x2c2137, 0x446176, 0x3fac95, 0xa1ef8c,
    0x2d162c, 0x412752, 0x683a68, 0x9775a6,
    0x161616, 0xab4646, 0x8f9bf6, 0xf0f0f0,
    0x40332f, 0x856d52, 0x95c798, 0xfbffe0,
};

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

void screen_set_palette(screen_t* screen, unsigned int p)
{
    screen->current_palette = p;
    PALETTE[0] = SCREEN_PALETTES[p * 4];
    PALETTE[1] = SCREEN_PALETTES[p * 4 + 1];
    PALETTE[2] = SCREEN_PALETTES[p * 4 + 2];
    PALETTE[3] = SCREEN_PALETTES[p * 4 + 3];
}

void screen_set_palette_game_next(screen_t* screen)
{
    unsigned int p = (screen->current_palette + 1) % (sizeof(SCREEN_PALETTES) / (sizeof(int) * 4));
    screen_set_palette(screen, p);
}

void screen_set_palette_random(screen_t* screen)
{
    int p = (int)(frandom() * (sizeof(SCREEN_PALETTES) / (sizeof(int) * 4)));
    screen_set_palette(screen, (unsigned int)p);
}


