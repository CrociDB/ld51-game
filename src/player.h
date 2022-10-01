#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "wasm4.h"
#include "bullet.h"

#define PLAYER_SPEED_ROTATION               .1f
#define PLAYER_SPEED                        .2f

typedef struct 
{
    float x;
    float y;

    float angle;
    float speed;

    bool input;

    bullet_t* bullets;
} player_t;

player_t* player_create();
void player_destroy(player_t* player);

void player_move(player_t* player);
void player_render(player_t* player);

#endif
