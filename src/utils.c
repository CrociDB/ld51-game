#include "utils.h"

#include <stdlib.h>
#include <math.h>

// distance stuff
float dist_sqf(float x1, float y1, float x2, float y2)
{
    float x = x1 - x2; 
    float y = y1 - y2; 
    return x * x + y * y;
}

// collisions
bool collision_sphere_sphere(   
    int x1, int y1, int r1,
    int x2, int y2, int r2)
{
    float r = (float)(r1 + r2);
    return dist_sq(x1, y1, x2, y2) <= r * r;
}

bool collision_point_sphere(
    int x1, int y1,
    int x2, int y2, int r2)
{
    return collision_sphere_sphere(x1, y1, 0, x2, y2, r2);
}

bool collision_point_line(
    int px, int py,
    int x1, int y1, int x2, int y2)
{
    float d1 = dist(px, py, x1, y1);
    float d2 = dist(px, py, x2, y2);
    float linelen = dist(x1, y1, x2, y2);
    static const float buffer = 0.1f;
    return d1 + d2 >= linelen && d1 + d2 <= linelen + buffer;
}

bool collision_line_sphere(
    int x1, int y1, int x2, int y2,
    int sx, int sy, int r)
{
    bool p1 = collision_point_sphere(x1, y1, sx, sy, r);
    bool p2 = collision_point_sphere(x2, y2, sx, sy, r);
    if (p1 || p2) return TRUE;

    float len = dist(x1, y1, x2, y2);
    float dot = (
        (((float)sx - (float)x1) * ((float)x2 - (float)x1)) + 
        (((float)sy - (float)y1) * ((float)y2 - (float)y1))) / powf(len,2);
    
    int cx = (int)((float)x1 + (dot * (float)(x2 - x1)));
    int cy = (int)((float)y1 + (dot * (float)(y2 - y1)));
    if (!collision_point_line(cx, cy, x1, y1, x2, y2)) return FALSE;

    return collision_point_sphere(cx, cy, sx, sy, r);
}
