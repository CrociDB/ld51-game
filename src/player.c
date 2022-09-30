#include "player.h"

const uint8_t PLAYER_SPRITE[] = {
    0b11000011,
    0b10000001,
    0b00100100,
    0b00100100,
    0b00000000,
    0b00100100,
    0b10011001,
    0b11000011,
};

player_t* player_create()
{
    player_t* p = (player_t*)malloc(sizeof(player_t));
    p->x = p->y = 0;
    return p;
}

void player_move(player_t* player)
{
    uint8_t gamepad = *GAMEPAD1;
    if (gamepad & BUTTON_LEFT)
        player->x -= PLAYER_SPEED;
    if (gamepad & BUTTON_RIGHT)
        player->x += PLAYER_SPEED;
    if (gamepad & BUTTON_UP)
        player->y -= PLAYER_SPEED;
    if (gamepad & BUTTON_DOWN)
        player->y += PLAYER_SPEED;
}

void player_render(player_t* player)
{
    text("Hello from Player!", 10, 10);
    blit(PLAYER_SPRITE, player->x, player->y, 8, 8, BLIT_1BPP);
}
