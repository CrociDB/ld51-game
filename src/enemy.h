#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "defs.h"

#define ENEMY_SIZE                  16
#define ENEMY_SPEED                 20

#define ENEMY_MAX_SECTIONS          50

typedef struct game_t game_t;

typedef struct
{
    float x;
    float y;
    bool active;
} shield_section_t;

typedef struct 
{
    float x;
    float y;

    int life;

    // for animation
    int frame;

    float shield_speed;
    float shield_max_size;
    float shield_size;
    float shield_angle;
    float shield_angle_speed;
    int shield_sections_sh;
    int shield_sections_op;
    shield_section_t* sections;

    int time_left;

    game_t* game;
} enemy_t;

enemy_t* enemy_create(game_t* game);
void enemy_destroy(enemy_t* enemy);

void enemy_update(enemy_t* enemy);
void enemy_render(enemy_t* enemy);

void _enemy_update_sections(enemy_t* enemy);

void _enemy_collision_player(enemy_t* enemy);
void _enemy_collision_bullets(enemy_t* enemy);
void _enemy_take_hit(enemy_t* enemy);

#endif
