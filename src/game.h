#ifndef _GAME_H_
#define _GAME_H_

#include "defs.h"
#include "player.h"
#include "particles.h"
#include "screen.h"
#include "enemy.h"

typedef enum 
{
    STATE_MENU = 0,
    STATE_GAME,
    STATE_NEXT_LEVEL,
    STATE_PREVIOUS_LEVEL,
    STATE_GAME_OVER
} game_state_e;

struct game_t
{
    player_t* player;
    particle_system_t* psystems;
    screen_t* screen;
    enemy_t* enemy;

    game_state_e state;

    int game_level;
};

void game_change_state(game_t* game, game_state_e state);

#endif
