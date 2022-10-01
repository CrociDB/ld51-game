#include "enemy.h"
#include "art.h"
#include "game.h"
#include "bullet.h"
#include "utils.h"

#include "wasm4.h"

#include <stdlib.h>
#include <memory.h>
#include <math.h>

enemy_t* enemy_create(game_t* game)
{
    enemy_t* enemy = (enemy_t*)malloc(sizeof(enemy_t));
    enemy->game = game;
    enemy->x = enemy->y = (SCREEN_SIZE - ENEMY_SIZE) / 2;
    enemy->shield_size = 10;

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

    enemy->shield_size = 10.0f + (sinf((float)(enemy->game->screen->game_frame) * .01f) * .5f + .5f) * 55.f; 

    // check collision
    _enemy_collision_bullets(enemy);
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

    *DRAW_COLORS = 3;

    float cx = enemy->x + sprite_enemyWidth / 2;
    float cy = enemy->y + sprite_enemyWidth / 2;

    int sections = 10 + (int)(enemy->shield_size * 1.0f);
    float section_arc = TWO_PI  / (float)sections;
    for (int i = 0; i < sections; i++)
     {
        int ni = (i + 1) % sections;

        int x = (int)(cx + sinf(section_arc * (float)i) * enemy->shield_size);
        int y = (int)(cy + cosf(section_arc * (float)i) * enemy->shield_size);

        int nx = (int)(cx + sinf(section_arc * (float)ni) * enemy->shield_size);
        int ny = (int)(cy + cosf(section_arc * (float)ni) * enemy->shield_size);

        line(x, y, nx, ny);
    }
}

void _enemy_collision_bullets(enemy_t* enemy)
{
    bullet_t* bullets = enemy->game->player->bullets;

    for (int i = 0; i < BULLETS_MAX; i++)
    {
        if (!bullets[i].active) continue;

        // hit shield
        if (collision_point_circle(
            (int)bullets[i].x, (int)bullets[i].y, 
            (int)enemy->x, (int)enemy->y, (int)enemy->shield_size))
        {
            _bullet_destroy(&bullets[i]);
        }
    }
}
