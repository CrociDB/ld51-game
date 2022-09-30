#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "wasm4.h"

#define PLAYER_SPEED            1

typedef struct 
{
    uint16_t x;
    uint16_t y;
} player_t;

player_t* player_create();
void player_move(player_t* player);
void player_render(player_t* player);

#endif