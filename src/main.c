#include "wasm4.h"

#include "game.h"

#include <stdlib.h>
#include <inttypes.h>

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
    game.screen = screen_create();
}

void update() 
{
    update_logic();
    update_render();    
}

void update_logic()
{
    switch(game.state)
    {
        case STATE_MENU:
        {
            uint8_t gamepad = *GAMEPAD1;
            if (gamepad & BUTTON_1) game_change_state(&game, STATE_GAME);
            break;
        }
        case STATE_GAME:
            player_move(game.player);
            enemy_update(game.enemy);
            break;
    }

    particle_update(game.psystems);
    screen_update(game.screen);
}

void update_render()
{
    switch(game.state)
    {
        case STATE_MENU:
            text("GAME LD51 - Main Menu", 10, 10);
            break;
        case STATE_GAME:
            enemy_render(game.enemy);
            player_render(game.player);
            break;
    }

    particle_render(game.psystems);
    screen_render(game.screen);
}

// state related stuff

void state_finish(game_t* game)
{
    switch(game->state)
    {
        case STATE_MENU:
            break;
        case STATE_GAME:
            player_destroy(game->player);
            enemy_destroy(game->enemy);
            break;
    }
}

void state_start(game_t* game)
{
    switch(game->state)
    {
        case STATE_MENU:
            break;
        case STATE_GAME:
            game->player = player_create(game);
            game->enemy = enemy_create(game);
            break;
    }
}

void game_change_state(game_t* game, game_state_e state)
{
    state_finish(game);
    game->state = state;
    state_start(game);
}


