#include "particles.h"
#include "wasm4.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

particle_system_t* particle_system_create()
{
    particle_system_t* psystems = (particle_system_t*)malloc(sizeof(particle_system_t) * PARTICLE_SYSTEM_MAX);
    for (int i = 0; i < PARTICLE_SYSTEM_MAX; i++)
    {
        psystems[i].particles = _particles_create();
        psystems[i].active = FALSE;
    }

    return psystems;
}

void particle_system_destroy(particle_system_t* psystems)
{
    for (int i = 0; i < PARTICLE_SYSTEM_MAX; i++)
    {
        _particles_destroy(psystems[i].particles);
    }

    free(psystems);
}

void particle_spawn(particle_system_t* psystems, float x, float y)
{
    for (int i = 0; i < PARTICLE_SYSTEM_MAX; i++)
    {
        if (psystems[i].active) continue;

        _particles_spawn(psystems[i].particles, x, y);
        psystems[i].active = TRUE;

        break;
    }
}

void particle_update(particle_system_t* psystems)
{
    for (int i = 0; i < PARTICLE_SYSTEM_MAX; i++)
    {
        if (!psystems[i].active) continue;

        bool active = _particles_update(psystems[i].particles);
        psystems[i].active = active;
    }
}

void particle_render(particle_system_t* psystems)
{
    for (int i = 0; i < PARTICLE_SYSTEM_MAX; i++)
    {
        if (!psystems[i].active) continue;

        _particles_render(psystems[i].particles);
    }
}


particle_t* _particles_create()
{
    particle_t* particles = (particle_t*)malloc(sizeof(particle_t) * PARTICLE_MAX);

    for (int i = 0; i < PARTICLE_MAX; i++)
    {
        particles[i].active = FALSE;
    }

    return particles;
}

void _particles_destroy(particle_t* p)
{
    free(p);
}


void _particles_spawn(particle_t* particles, float x, float y)
{
    for (int i = 0; i < PARTICLE_MAX; i++)
    {
        particles[i].x = x;
        particles[i].y = y;
        particles[i].angle = frandom() * (PI * 2.0f);
        particles[i].speed = frandom() * PARTICLE_MAX_SPEED + PARTICLE_MIN_SPEED;

        particles[i].max_life = (int)(frandom() * PARTICLE_MAX_LIFE) + PARTICLE_MIN_LIFE;
        particles[i].life = 0;

        particles[i].active = TRUE;
    }
}

bool _particles_update(particle_t* particles)
{
    int total = 0;
    for (int i = 0; i < PARTICLE_MAX; i++)
    {
        if (!particles[i].active) continue;

        float dx = sinf(particles[i].angle) * particles[i].speed;
        float dy = cosf(particles[i].angle) * particles[i].speed;

        particles[i].x += dx;
        particles[i].y += dy;

        if (particles[i].life++ > particles[i].max_life || particles[i].life < 0)
            particles[i].active = FALSE;

        total++;
    }

    return total > 0;
}

void _particles_render(particle_t* particles)
{
    *DRAW_COLORS = 3;

    for (int i = 0; i < PARTICLE_MAX; i++)
    {
        if (!particles[i].active) continue;

        rect((int)particles[i].x, (int)particles[i].y, 1, 1);
    }
}
