#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "defs.h"

#include <inttypes.h>

#define PARTICLE_SYSTEM_MAX             10
#define PARTICLE_MAX                    20

#define PARTICLE_MIN_SPEED              0.5f
#define PARTICLE_MAX_SPEED              2.0f
#define PARTICLE_MIN_LIFE               50
#define PARTICLE_MAX_LIFE               100

typedef struct 
{
    float x;
    float y;
    float angle;
    float speed;

    int life;
    int max_life;

    bool active;
} particle_t;

typedef struct
{
    particle_t* particles;
    bool active;
} particle_system_t;


particle_system_t* particle_system_create();
void particle_system_destroy(particle_system_t* psystem);

void particle_spawn(particle_system_t* psystems, float x, float y);

void particle_update(particle_system_t* psystems);
void particle_render(particle_system_t* psystems);

particle_t* _particles_create();
void _particles_spawn(particle_t* particles, float x, float y);
bool _particles_update(particle_t* particles);
void _particles_render(particle_t* particles);
void _particles_destroy(particle_t* p);

#endif
