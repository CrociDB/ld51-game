#include "wasm4.h"

#include "game.h"
#include "utils.h"
#include "artmenu.h"

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void update_logic();
void update_render();

game_t game;
void game_render();

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
    uint8_t gamepad = *GAMEPAD1;
    switch(game.state)
    {
        case STATE_MENU:
        {
            if (gamepad & BUTTON_1 && game.screen->game_frame > 30) game_change_state(&game, STATE_GAME);
            break;
        }
        case STATE_GAME:
            if (game.screen->game_frame > 30) player_move(game.player);
            enemy_update(game.enemy);
            break;
        case STATE_NEXT_LEVEL:
        {
            if (game.screen->game_frame > 60)
            {
                game.game_level++;
                game_change_state(&game, STATE_GAME);
            }
            break;
        }
        case STATE_GAME_OVER:
        {
            if (game.screen->game_frame > 30)
            {
                if (gamepad & BUTTON_1 && game.screen->game_frame > 60)
                    game_change_state(&game, STATE_MENU);
            }
            break;
        }
    }

    particle_update(game.psystems);
    screen_update(game.screen);
}

void update_render()
{
    switch(game.state)
    {
        case STATE_MENU:
        {
            *DRAW_COLORS = 0x3142;
            blit(
                spacelord, 
                10, 10, 
                spacelordWidth, spacelordHeight, 
                spacelordFlags);
                
            *DRAW_COLORS = 3;
            text("Press \x80 to play", 21, 120);
            break;
        }
        case STATE_GAME:
            game_render();
            break;
        case STATE_NEXT_LEVEL:
            break;
        case STATE_GAME_OVER:
        {
            *DRAW_COLORS = 0x3142;
            blit(
                spacelord, 
                19, 65, 
                spacelordWidth, spacelordHeight, 
                spacelordFlags);

            
            *DRAW_COLORS = 4;
            text("Game Over", 49, 10);

            
            *DRAW_COLORS = 3;
            text("Level:", 10, 40);
            char buffer[64];
            itoa(buffer, game.game_level);
            text(buffer, 60, 40);
            break;
        }
    }

    particle_render(game.psystems);
    screen_render(game.screen);
}

void game_render()
{
    enemy_render(game.enemy);
    player_render(game.player);

    // game hud
    char level[64];
    itoa(level, game.game_level);
    text(level, 4, 4);
}

// state related stuff

void state_finish(game_t* game)
{
    switch(game->state)
    {
        case STATE_MENU:
            game->game_level = 1;
            break;
        case STATE_GAME:
            player_destroy(game->player);
            enemy_destroy(game->enemy);
            break;
        case STATE_NEXT_LEVEL:
            break;
        case STATE_GAME_OVER:
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
        case STATE_NEXT_LEVEL:
        {
            for (int i = 0; i < 5; i++)
                particle_spawn(game->psystems, SCREEN_SIZE / 2, SCREEN_SIZE / 2);
            break;
        }
        case STATE_GAME_OVER:
            break;
    }
}

void game_change_state(game_t* game, game_state_e state)
{
    state_finish(game);
    game->state = state;
    state_start(game);

    game->screen->game_frame = 0;
}


