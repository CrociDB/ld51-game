#ifndef _BULLET_H_
#define _BULLET_H_

#include <stdlib.h>
#include <stdio.h>

#include "defs.h"

#define BULLETS_MAX                   10
#define BULLETS_SPEED                 3.0f

typedef struct game_t game_t;

typedef struct 
{
    float x;
    float y;
    float angle;
    float speed;

    bool active;

    game_t* game;
} bullet_t;

bullet_t* bullet_create_system(game_t* game);
void bullet_destroy_system(bullet_t* bullets);

void bullet_update(bullet_t* bullets);
void bullet_render(bullet_t* bullets);

void bullet_spawn(bullet_t* bullets, float x, float y, float angle);

void _bullet_destroy(bullet_t* bullets);

#endif