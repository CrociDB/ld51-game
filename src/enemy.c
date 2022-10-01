#include "enemy.h"
#include "art.h"
#include "game.h"
#include "wasm4.h"

#include <stdlib.h>
#include <memory.h>

enemy_t* enemy_create(game_t* game)
{
    enemy_t* enemy = (enemy_t*)malloc(sizeof(enemy_t));
    enemy->game = game;
    enemy->x = enemy->y = (SCREEN_SIZE - ENEMY_SIZE) / 2;

    return enemy;
}

void enemy_destroy(enemy_t* enemy)
{
    free(enemy);
}

void enemy_update(enemy_t* enemy)
{
    enemy->x = enemy->y = (SCREEN_SIZE - ENEMY_SIZE) / 2;
    if (((enemy->game->screen->game_frame) % ENEMY_SPEED) == 0)
        enemy->frame = (enemy->frame + 1) % 2;
}

void enemy_render(enemy_t* enemy)
{
    *DRAW_COLORS = 0x1324;
    blitSub(
        sprite_enemy, 
        (int)enemy->x, (int)enemy->y, 
        sprite_enemyWidth, sprite_enemyWidth, 
        0, (uint32_t)enemy->frame * sprite_enemyWidth, 
        16, sprite_enemyFlags);
}
