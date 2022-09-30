#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "wasm4.h"

typedef struct 
{
    uint8_t x;
    uint8_t y;
} player_t;

player_t* player_create();
void player_render(player_t* player);

#endif
