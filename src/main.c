#include "wasm4.h"

#include "player.h"

void update_logic();
void update_render();

player_t* player;


void start()
{
    player = player_create();
}

void update() 
{
    update_logic();
    update_render();    
}

void update_logic()
{
    player_move(player);
}

void update_render()
{
    *DRAW_COLORS = 2;
    
    //text("Text sample", 10, 10);

    player_render(player);
}
