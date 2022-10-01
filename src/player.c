#include "player.h"

#include <math.h>

#define PI                              3.1415926f
#define PI_2                            1.5707963f
#define PI_4                            0.78539815f

#define clamp(X, XMIN, XMAX)           (X > XMAX ? XMAX : (X < XMIN ? XMIN : X))

player_t* player_create()
{
    player_t* p = (player_t*)malloc(sizeof(player_t));
    p->x = p->y = 30;
    return p;
}

void player_move(player_t* player)
{
    uint8_t gamepad = *GAMEPAD1;
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

    int dx = (int)(sinf(player->angle) * max_speed);
    int dy = (int)(cosf(player->angle) * max_speed);

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
}

void player_render(player_t* player)
{
    int dx = (int)(sinf(player->angle) * 8.0f) + player->x;
    int dy = (int)(cosf(player->angle) * 8.0f) + player->y;

    int lx = (int)(sinf(player->angle + PI_2) * 4.0f) + player->x;
    int ly = (int)(cosf(player->angle + PI_2) * 4.0f) + player->y;
    int kx = (int)(sinf(player->angle - PI_2) * 4.0f) + player->x;
    int ky = (int)(cosf(player->angle - PI_2) * 4.0f) + player->y;

    // line(player->x, player->y, dx, dy);
    line(dx, dy, lx, ly);
    line(dx, dy, kx, ky);
    line(lx, ly, kx, ky);
    // line(player->x, player->y, dx, dy);
}
