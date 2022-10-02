#include "player.h"
#include "defs.h"
#include "utils.h"
#include "bullet.h"

#include <math.h>

player_t* player_create(game_t* game)
{
    player_t* p = (player_t*)malloc(sizeof(player_t));
    p->x = p->y = 30;

    p->bullets = bullet_create_system(game);

    p->game = game;

    return p;
}

void player_destroy(player_t* player)
{
    bullet_destroy_system(player->bullets);
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

    if (gamepad & BUTTON_UP || gamepad & BUTTON_2)
        player->speed += PLAYER_SPEED;
    if (gamepad & BUTTON_DOWN)
        player->speed -= PLAYER_SPEED;

    player->speed *= .95f;
    
    float max_speed = fclamp(player->speed, -3.0f, 3.0f);

    float dx = sinf(player->angle) * max_speed;
    float dy = cosf(player->angle) * max_speed;

    player->x += dx;
    player->y += dy;

    // screen collisions
    if (player->x > SCREEN_SIZE + 6)
    {
        player->x = -5.0f;
    }
    if (player->x < -6.0f)
    {
        player->x = (float)SCREEN_SIZE + 5.0f;
    }

    if (player->y > SCREEN_SIZE + 6)
    {
        player->y = -5.0f;
    }
    if (player->y < -6.0f)
    {
        player->y = (float)SCREEN_SIZE + 5.0f;
    }

    bullet_update(player->bullets);
}

void player_render(player_t* player)
{
    *DRAW_COLORS = 4;

    int dx = (int)(sinf(player->angle) * 8.0f + player->x);
    int dy = (int)(cosf(player->angle) * 8.0f + player->y);

    int lx = (int)(sinf(player->angle + PI_2) * 5.0f + player->x);
    int ly = (int)(cosf(player->angle + PI_2) * 5.0f + player->y);
    int kx = (int)(sinf(player->angle - PI_2) * 5.0f + player->x);
    int ky = (int)(cosf(player->angle - PI_2) * 5.0f + player->y);

    line(dx, dy, lx, ly);
    line(dx, dy, kx, ky);
    line(lx, ly, kx, ky);

    *DRAW_COLORS = 0x42;
    oval(   (int)player->x - 3, (int)player->y - 3, 
            6, 6);
    
    bullet_render(player->bullets);
}
