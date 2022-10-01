#ifndef _UTILS_H_
#define _UTILS_H_

#include "defs.h"

// distance stuff
float dist_sqf(float x1, float y1, float x2, float y2);

inline float dist_sq(int x1, int y1, int x2, int y2)
{
    return dist_sqf((float)x1, (float)y1, (float)x2, (float)y2);
}

inline float dist(int x1, int y1, int x2, int y2)
{
    return sqrtf(dist_sqf((float)x1, (float)y1, (float)x2, (float)y2));
}

// collisions
bool collision_sphere_sphere(   
    int x1, int y1, int r1,
    int x2, int y2, int r2);

bool collision_point_sphere(
    int x1, int y1,
    int x2, int y2, int r2);


bool collision_point_line(
    int px, int py,
    int x1, int y1, int x2, int y2);

bool collision_line_sphere(
    int x1, int y1, int x2, int y2,
    int sx, int sy, int r);

#endif
