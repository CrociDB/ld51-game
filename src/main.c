#include "wasm4.h"

#include "player.h"
#include "particles.h"

// #include <time.h>
#include <stdlib.h>

void update_logic();
void update_render();

player_t* player;
particle_system_t* psystems;

void start()
{
    // srand((unsigned)time(NULL));
    PALETTE[0] = 0xfff6d3;
    PALETTE[1] = 0xf9a875;
    PALETTE[2] = 0xeb6b6f;
    PALETTE[3] = 0x7c3f58;

    psystems = particle_system_create();
    player = player_create();
}

void update() 
{
    update_logic();
    update_render();    
}

void update_logic()
{
    player_move(player);
}

void update_render()
{
    //text("Text sample", 10, 10);

    player_render(player);
}
