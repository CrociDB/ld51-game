#ifndef _GAME_H_
#define _GAME_H_

#include "defs.h"
#include "player.h"
#include "particles.h"

struct game_t
{
    player_t* player;
    particle_system_t* psystems;
};

#endif
