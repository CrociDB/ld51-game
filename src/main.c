#include "wasm4.h"

#include "game.h"

#include <stdlib.h>

void update_logic();
void update_render();

game_t game;

void start()
{
    PALETTE[0] = 0xfff6d3;
    PALETTE[1] = 0xf9a875;
    PALETTE[2] = 0xeb6b6f;
    PALETTE[3] = 0x7c3f58;

    game.psystems = particle_system_create();
    game.player = player_create(&game);
    game.screen = screen_create();
    game.enemy = enemy_create(&game);
}

void update() 
{
    update_logic();
    update_render();    
}

void update_logic()
{
    player_move(game.player);
    enemy_update(game.enemy);
    particle_update(game.psystems);

    screen_update(game.screen);
}

void update_render()
{
    player_render(game.player);
    enemy_render(game.enemy);
    particle_render(game.psystems);

    screen_render(game.screen);
}
