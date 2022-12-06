#include "game.h"
#include "bullet.h"
#include "defs.h"
#include "particles.h"
#include "audio.h"
#include "wasm4.h"

#include <malloc.h>
#include <math.h>

bullet_t* bullet_create_system(game_t* game)
{
    bullet_t* b = (bullet_t*)malloc(sizeof(bullet_t) * BULLETS_MAX);
    for (int i = 0; i < BULLETS_MAX; i++)
    {
        b[i].active = FALSE;
        b[i].game = game;
    }

    return b;
}

void bullet_destroy_system(bullet_t* bullets)
{
    free(bullets);
}

void bullet_update(bullet_t* bullets)
{
    for (int i = 0; i < BULLETS_MAX; i++)
    {
        if (!bullets[i].active) continue;

        float dx = sinf(bullets[i].angle) * BULLETS_SPEED;
        float dy = cosf(bullets[i].angle) * BULLETS_SPEED;

        bullets[i].x += dx;
        bullets[i].y += dy;

        if (bullets[i].x > SCREEN_SIZE || bullets[i].x < 0) 
        {
            audio_play_crash();
            _bullet_destroy(&bullets[i]);
        }
        if (bullets[i].y > SCREEN_SIZE || bullets[i].y < 0) 
        {
            audio_play_crash();
            _bullet_destroy(&bullets[i]);
        }
    }
}

void bullet_render(bullet_t* bullets)
{
    *DRAW_COLORS = 2;
    for (int i = 0; i < BULLETS_MAX; i++)
    {
        if (!bullets[i].active) continue;

        int dx = (int)(sinf(bullets[i].angle + PI) * 4.0f + bullets[i].x);
        int dy = (int)(cosf(bullets[i].angle + PI) * 4.0f + bullets[i].y);

        line((int)bullets[i].x, (int)bullets[i].y, dx, dy);
    }
}

void bullet_spawn(bullet_t* bullets, float x, float y, float angle)
{
    for (int i = 0; i < BULLETS_MAX; i++)
    {
        if (bullets[i].active) continue;

        bullets[i].x = (float)x;
        bullets[i].y = (float)y;
        bullets[i].angle = angle;
        bullets[i].active = TRUE;

        break;
    }
}

void _bullet_destroy(bullet_t* bullets)
{
    bullets->active = FALSE;
    screen_shake(bullets->game->screen, 5, 2);
    particle_spawn(bullets->game->psystems, bullets->x, bullets->y);
}
