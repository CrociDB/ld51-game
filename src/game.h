#ifndef _GAME_H_
#define _GAME_H_

#include "defs.h"
#include "player.h"
#include "particles.h"
#include "screen.h"
#include "enemy.h"

struct game_t
{
    player_t* player;
    particle_system_t* psystems;
    screen_t* screen;
    enemy_t* enemy;
};

#endif
