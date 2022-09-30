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

void player_render(player_t* player)
{
    blit(PLAYER_SPRITE, player->x, player->y, 8, 8, BLIT_1BPP);
}
