#include "enemy.h"
#include "art.h"
#include "game.h"
#include "bullet.h"
#include "utils.h"

#include "wasm4.h"

#include <stdlib.h>
#include <memory.h>
#include <math.h>

enemy_t* enemy_create(game_t* game)
{
    enemy_t* enemy = (enemy_t*)malloc(sizeof(enemy_t));
    enemy->game = game;
    enemy->x = enemy->y = SCREEN_SIZE / 2;
    enemy->shield_size = 10;
    enemy->life = 2 + game->game_level * 2;
    
    enemy->shield_speed = .01f + (float)game->game_level * .001f;
    enemy->shield_angle_speed = .01f + (float)game->game_level * .002f;
    enemy->shield_angle_speed *= (frandom() < .5f ? -1 : 1);
    
    enemy->shield_max_size = 30.0f + (float)game->game_level * 1.2f;

    enemy->shield_sections_sh = 2 + (int)((float)game->game_level * .3f);
    float open = (float)game->game_level * .1f;
    open = 5.0f - (open > 4.0f ? 4.0f : open) + frandom() * 2.0f;
    enemy->shield_sections_op = (int)open;

    enemy->sections = (shield_section_t*)malloc(sizeof(shield_section_t) * ENEMY_MAX_SECTIONS);

    return enemy;
}

void enemy_destroy(enemy_t* enemy)
{
    free(enemy->sections);
    free(enemy);
}

void enemy_update(enemy_t* enemy)
{
    if (((enemy->game->screen->game_frame) % ENEMY_SPEED) == 0)
        enemy->frame = (enemy->frame + 1) % 2;

    enemy->shield_size = 12.0f + (sinf((float)(enemy->game->screen->game_frame) * enemy->shield_speed) * .5f + .5f) * enemy->shield_max_size; 

    enemy->shield_angle += enemy->shield_angle_speed;

    // update sections
    _enemy_update_sections(enemy);

    // check collision
    _enemy_collision_bullets(enemy);
    _enemy_collision_player(enemy);
}

void enemy_render(enemy_t* enemy)
{
    *DRAW_COLORS = 0x1324;

    int sprite_x = (int)(enemy->x - ENEMY_SIZE / 2.0f);
    int sprite_y = (int)(enemy->y - ENEMY_SIZE / 2.0f);

    blitSub(
        sprite_enemy, 
        sprite_x, sprite_y, 
        sprite_enemyWidth, sprite_enemyWidth, 
        0, (uint32_t)enemy->frame * sprite_enemyWidth, 
        16, sprite_enemyFlags);

    *DRAW_COLORS = 3;

    for (int i = 0; i < ENEMY_MAX_SECTIONS; i++)
    {
        if (!enemy->sections[i].active) continue;

        int ni = (i + 1) % ENEMY_MAX_SECTIONS;

        line(
            (int)enemy->sections[i].x, 
            (int)enemy->sections[i].y, 
            (int)enemy->sections[ni].x, 
            (int)enemy->sections[ni].y);
    }
}

void _enemy_update_sections(enemy_t* enemy)
{
    int sections = ENEMY_MAX_SECTIONS;
    float section_arc = TWO_PI  / (float)sections;
    for (int i = 0; i < ENEMY_MAX_SECTIONS; i++)
    {
        int opcount = i % (enemy->shield_sections_sh + enemy->shield_sections_op);
        enemy->sections[i].active = opcount >= enemy->shield_sections_op;

        float x = enemy->x + sinf(section_arc * (float)i + enemy->shield_angle) * enemy->shield_size;
        float y = enemy->y + cosf(section_arc * (float)i + enemy->shield_angle) * enemy->shield_size;

        enemy->sections[i].x = x;
        enemy->sections[i].y = y;
    }
}

void _enemy_collision_player(enemy_t* enemy)
{
    bullet_t* bullets = enemy->game->player->bullets;

    bool collide = FALSE;

    float psize = PLAYER_SIZE / 1.5f;

    // core
    collide = collision_circle_circle(enemy->x, enemy->y, ENEMY_SIZE / 1.6f,
            enemy->game->player->x, enemy->game->player->y, psize);
    
    // shield
    bool precol = (collision_circle_circle(enemy->x, enemy->y, enemy->shield_size,
                enemy->game->player->x, enemy->game->player->y, psize) && 
            !collision_circle_circle(enemy->x, enemy->y, enemy->shield_size - 3,
                enemy->game->player->x, enemy->game->player->y, psize));
    if (precol)
    {
        // inside she shield area, collide now with every section
        int sections = ENEMY_MAX_SECTIONS;
        float section_arc = TWO_PI  / (float)sections;
        for (int j = 0; j < ENEMY_MAX_SECTIONS; j++)
        {
            if (!enemy->sections[j].active) continue;

            int nj = (j + 1) % ENEMY_MAX_SECTIONS;
            bool collide_circle_line = collision_line_circle(
                enemy->sections[j].x, enemy->sections[j].y,
                enemy->sections[nj].x, enemy->sections[nj].y,
                enemy->game->player->x, enemy->game->player->y, psize);
            
            if (collide_circle_line)
            {
                collide = collide || TRUE;
                break;
            }
        }
    }

    if (collide)
    {
        particle_spawn(enemy->game->psystems, enemy->game->player->x, enemy->game->player->x);
        game_change_state(enemy->game, STATE_GAME_OVER);
    }
}

void _enemy_collision_bullets(enemy_t* enemy)
{
    bullet_t* bullets = enemy->game->player->bullets;

    for (int i = 0; i < BULLETS_MAX; i++)
    {
        if (!bullets[i].active) continue;

        // hit shield
        if (collision_point_circle(bullets[i].x, bullets[i].y, 
                enemy->x, enemy->y, enemy->shield_size) && 
            !collision_point_circle(bullets[i].x, bullets[i].y, 
                enemy->x, enemy->y, enemy->shield_size - 3))
        {
            // inside she shield area, collide now with every section
            int sections = ENEMY_MAX_SECTIONS;
            float section_arc = TWO_PI  / (float)sections;
            for (int j = 0; j < ENEMY_MAX_SECTIONS; j++)
            {
                if (!enemy->sections[j].active) continue;

                int nj = (j + 1) % ENEMY_MAX_SECTIONS;
                bool collide_circle_line = collision_line_circle(
                    enemy->sections[j].x, enemy->sections[j].y,
                    enemy->sections[nj].x, enemy->sections[nj].y,
                    bullets[i].x, bullets[i].y, 3);
                
                if (collide_circle_line)
                {
                    _bullet_destroy(&bullets[i]);
                    break;
                }
            }
        }

        // hit core
        if (collision_point_circle(bullets[i].x, bullets[i].y, 
                enemy->x, enemy->y, (float)ENEMY_SIZE / 1.414f))
        {
            _bullet_destroy(&bullets[i]);
            _enemy_take_hit(enemy);
        }
    }
}

void _enemy_take_hit(enemy_t* enemy)
{
    if (--enemy->life <= 0)
    {
        game_change_state(enemy->game, STATE_NEXT_LEVEL);
    }
}
