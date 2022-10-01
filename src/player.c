#include "player.h"
#include "defs.h" 

#include <math.h>

#define clamp(X, XMIN, XMAX)           (X > XMAX ? XMAX : (X < XMIN ? XMIN : X))

player_t* player_create()
{
    player_t* p = (player_t*)malloc(sizeof(player_t));
    p->x = p->y = 30;

    p->bullets = bullet_create_system();

    return p;
}

void player_destroy(player_t* player)
{
    bullet_destroy(player->bullets);
    free(player);
}

void player_move(player_t* player)
{
    uint8_t gamepad = *GAMEPAD1;

    if (gamepad & BUTTON_1)
    {
        if (!player->input)
        {
            float dx = sinf(player->angle) * 8.0f + player->x;
            float dy = cosf(player->angle) * 8.0f + player->y;
            bullet_spawn(player->bullets, dx, dy, player->angle);
            player->input = TRUE;
        }
    }
    else
    {
        player->input = FALSE;
    }

    if (gamepad & BUTTON_LEFT)
        player->angle += PLAYER_SPEED_ROTATION;
    if (gamepad & BUTTON_RIGHT)
        player->angle -= PLAYER_SPEED_ROTATION;

    if (gamepad & BUTTON_UP)
        player->speed += PLAYER_SPEED;
    if (gamepad & BUTTON_DOWN)
        player->speed -= PLAYER_SPEED;

    player->speed *= .95f;
    
    float max_speed = clamp(player->speed, -3.0f, 3.0f);

    float dx = sinf(player->angle) * max_speed;
    float dy = cosf(player->angle) * max_speed;

    player->x += dx;
    player->y += dy;

    // screen collisions
    if (player->x > SCREEN_SIZE - 1)
    {
        player->x = SCREEN_SIZE - 1;
        player->angle += PI;
        player->speed *= .3f;
    }
    if (player->x < 0)
    {
        player->x = 0;
        player->angle -= PI;
        player->speed *= .3f;
    }

    if (player->y > SCREEN_SIZE - 1)
    {
        player->y = SCREEN_SIZE - 1;
        player->angle += PI;
        player->speed *= .3f;
    }
    if (player->y < 0)
    {
        player->y = 0;
        player->angle -= PI;
        player->speed *= .3f;
    }

    bullet_update(player->bullets);
}

void player_render(player_t* player)
{
    int dx = (int)(sinf(player->angle) * 8.0f + player->x);
    int dy = (int)(cosf(player->angle) * 8.0f + player->y);

    int lx = (int)(sinf(player->angle + PI_2) * 4.0f + player->x);
    int ly = (int)(cosf(player->angle + PI_2) * 4.0f + player->y);
    int kx = (int)(sinf(player->angle - PI_2) * 4.0f + player->x);
    int ky = (int)(cosf(player->angle - PI_2) * 4.0f + player->y);

    line(dx, dy, lx, ly);
    line(dx, dy, kx, ky);
    line(lx, ly, kx, ky);
    
    bullet_render(player->bullets);
}
