#include "game.h"
#include "missile.h"
#include "defs.h"
#include "particles.h"

missile_t* missile_create_system(game_t* game)
{
    missile_t* m = (missile_t*)malloc(sizeof(missile_t) * MISSILES_MAX);
    for (int i = 0; i < MISSILES_MAX; i++)
    {
        m[i].active = FALSE;
        m[i].game = game;
        m[i].speed = .5f + ((float)game->game_level * .3f) + (frandom() * 2.0f);
    }

    return m;
}

void missile_destroy_system(missile_t* missiles)
{
    free(missiles);
}

void missile_update(missile_t* missiles)
{
    for (int i = 0; i < MISSILES_MAX; i++)
    {
        if (!missiles[i].active) continue;

        float dx = sinf(missiles[i].angle) * missiles->speed;
        float dy = cosf(missiles[i].angle) * missiles->speed;

        missiles[i].x += dx;
        missiles[i].y += dy;

        if (missiles[i].x > SCREEN_SIZE || missiles[i].x < 0) _missile_destroy(&missiles[i]);
        if (missiles[i].y > SCREEN_SIZE || missiles[i].y < 0) _missile_destroy(&missiles[i]);
    }
}

void missile_render(missile_t* missiles)
{
    *DRAW_COLORS = 3;
    for (int i = 0; i < MISSILES_MAX; i++)
    {
        if (!missiles[i].active) continue;

        int dx = (int)(sinf(missiles[i].angle + PI) * 6.0f + missiles[i].x);
        int dy = (int)(cosf(missiles[i].angle + PI) * 6.0f + missiles[i].y);

        line((int)missiles[i].x, (int)missiles[i].y, dx, dy);
    }
}

void missile_spawn(missile_t* missiles, float x, float y, float angle)
{
    for (int i = 0; i < MISSILES_MAX; i++)
    {
        if (missiles[i].active) continue;

        missiles[i].x = (float)x;
        missiles[i].y = (float)y;
        missiles[i].angle = angle;
        missiles[i].active = TRUE;

        break;
    }
}

void _missile_destroy(missile_t* missile)
{
    missile->active = FALSE;
    screen_shake(missile->game->screen, 10, 4);
    particle_spawn(missile->game->psystems, missile->x, missile->y);
}
