#ifndef _UTILS_H_
#define _UTILS_H_

#include "defs.h"

#define fclamp(X, XMIN, XMAX)           (X > XMAX ? XMAX : (X < XMIN ? XMIN : X))

static char *itoa_simple_helper(char *dest, int i) 
{
    if (i <= -10) 
    {
        dest = itoa_simple_helper(dest, i/10);
    }
    *dest++ = '0' - i%10;
    return dest;
}

char *itoa(char *dest, int i);

float lerp(float a, float b, float t);

// angle stuff
float angle_points(float x1, float y1, float x2, float y2);

// distance stuff
float dist_sq(float x1, float y1, float x2, float y2);

inline float dist(float x1, float y1, float x2, float y2)
{
    return sqrtf(dist_sq(x1, y1, x2, y2));
}

// collisions
bool collision_circle_circle(   
    float x1, float y1, float r1,
    float x2, float y2, float r2);

bool collision_point_circle(
    float x1, float y1,
    float x2, float y2, float r2);


bool collision_point_line(
    float px, float py,
    float x1, float y1, float x2, float y2);

bool collision_line_circle(
    float x1, float y1, float x2, float y2,
    float sx, float sy, float r);

#endif
