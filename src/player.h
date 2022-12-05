#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "wasm4.h"
#include "bullet.h"

#define PLAYER_SPEED_ROTATION               .13f
#define PLAYER_SPEED                        .1f
#define PLAYER_SPEED_MAX                    9.5f
#define PLAYER_SHOOT_DELAY                  1.5f

#define PLAYER_SIZE                         4.0f

typedef struct game_t game_t;

typedef struct 
{
    float x;
    float y;

    float angle;
    float speed;

    float input_delay;

    bullet_t* bullets;

    // only references
    game_t* game;
} player_t;

player_t* player_create(game_t* game);
void player_destroy(player_t* player);

void player_move(player_t* player);
void player_render(player_t* player);

#endif
