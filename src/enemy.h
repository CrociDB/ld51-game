#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "defs.h"

#define ENEMY_SIZE                  16

typedef struct game_t game_t;

typedef struct 
{
    float x;
    float y;

    int frame;

    game_t* game;
} enemy_t;

enemy_t* enemy_create(game_t* game);
void enemy_destroy(enemy_t* enemy);

void enemy_update(enemy_t* enemy);
void enemy_render(enemy_t* enemy);

#endif
