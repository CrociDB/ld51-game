#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdio.h>
#include <inttypes.h>

#define PI              3.1415926f
#define PI_2            1.5707963f
#define PI_4            0.78539815f

typedef uint8_t         bool;
#define TRUE            1
#define FALSE           0

#define frandom()        ((float)rand() / (float)(RAND_MAX))

#endif