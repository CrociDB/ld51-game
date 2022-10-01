#include "enemy.h"
#include "wasm4.h"

#include <stdlib.h>
#include <memory.h>

enemy_t* enemy_create()
{
    enemy_t* enemy = (enemy_t*)malloc(sizeof(enemy_t));
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
}

void enemy_render(enemy_t* enemy)
{
    *DRAW_COLORS = 4;
    oval((int)enemy->x, (int)enemy->y, 16, 16);
}
