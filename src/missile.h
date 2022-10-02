#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <stdlib.h>
#include <stdio.h>

#include "defs.h"

#define MISSILES_MAX                   10

typedef struct game_t game_t;

typedef struct 
{
    float x;
    float y;
    float angle;
    float speed;

    bool active;

    game_t* game;
} missile_t;

missile_t* missile_create_system(game_t* game);
void missile_destroy_system(missile_t* missiles);

void missile_update(missile_t* missiles);
void missile_render(missile_t* missiles);

void missile_spawn(missile_t* missiles, float x, float y, float angle);

void _missile_destroy(missile_t* missile);

#endif