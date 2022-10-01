#include "wasm4.h"

#include "game.h"

// #include <time.h>
#include <stdlib.h>

void update_logic();
void update_render();

game_t game;

void start()
{
    // srand((unsigned)time(NULL));
    PALETTE[0] = 0xfff6d3;
    PALETTE[1] = 0xf9a875;
    PALETTE[2] = 0xeb6b6f;
    PALETTE[3] = 0x7c3f58;

    game.psystems = particle_system_create();
    game.player = player_create(&game);
}

void update() 
{
    update_logic();
    update_render();    
}

void update_logic()
{
    player_move(game.player);
    particle_update(game.psystems);
}

void update_render()
{
    //text("Text sample", 10, 10);

    player_render(game.player);
    particle_render(game.psystems);
}
