#include "utils.h"

#include <stdlib.h>
#include <math.h>

char *itoa(char *dest, int i)
{
    char *s = dest;
    if (i < 0) 
    {
        *s++ = '-';
    } else 
    {
        i = -i;
    }

    *itoa_simple_helper(s, i) = '\0';
    return dest;
}

// distance stuff
float dist_sq(float x1, float y1, float x2, float y2)
{
    float x = x1 - x2; 
    float y = y1 - y2; 
    return x * x + y * y;
}

// collisions
bool collision_circle_circle(   
    float x1, float y1, float r1,
    float x2, float y2, float r2)
{
    float r = r1 + r2;
    return dist_sq(x1, y1, x2, y2) <= r * r;
}

bool collision_point_circle(
    float x1, float y1,
    float x2, float y2, float r2)
{
    return collision_circle_circle(x1, y1, 0, x2, y2, r2);
}

bool collision_point_line(
    float px, float py,
    float x1, float y1, float x2, float y2)
{
    float d1 = dist(px, py, x1, y1);
    float d2 = dist(px, py, x2, y2);
    float linelen = dist(x1, y1, x2, y2);
    static const float buffer = 0.1f;
    return d1 + d2 >= linelen && d1 + d2 <= linelen + buffer;
}

bool collision_line_circle(
    float x1, float y1, float x2, float y2,
    float sx, float sy, float r)
{
    bool p1 = collision_point_circle(x1, y1, sx, sy, r);
    bool p2 = collision_point_circle(x2, y2, sx, sy, r);
    if (p1 || p2) return TRUE;

    float len = dist(x1, y1, x2, y2);
    float dot = (
        (sx - x1) * (x2 - x1) + 
        (sy - y1) * (y2 - y1)) / powf(len, 2);
    
    float cx = x1 + (dot * (x2 - x1));
    float cy = y1 + (dot * (y2 - y1));
    if (!collision_point_line(cx, cy, x1, y1, x2, y2)) return FALSE;

    return collision_point_circle(cx, cy, sx, sy, r);
}
