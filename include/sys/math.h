#ifndef SYSTEM_MATH_H
#define SYSTEM_MATH_H

#include "types.h"

/* 4096 is 1.0 and one turn; angles use the same unit. */
#ifndef ONE
#define ONE 4096
#endif

/* Fixed-point multiply by 1.0 (ONE): two ONE-scaled values, result ONE-scaled. */
#define FIXED_MUL(a, b) (((a) * (b)) >> 12)

/* One turn of the fixed-point angle unit. */
#define ANGLE_MASK      (ONE - 1)

/* Whole-degree angles in the 4096-unit turn; ONE is the full turn. */
#define ANGLE_45        (ONE / 8)
#define ANGLE_90        (ONE / 4)
#define ANGLE_180       (ONE / 2)
#define ANGLE_270       (ONE * 3 / 4)

/* A degree count converted to the 4096-unit angle at run time. */
#define DEG(degrees)    ((degrees) * ONE / 360)

/* In-place integer lower bound. */
#define CLAMP_MIN(value, min)  \
    do {                       \
        if ((value) < (min)) { \
            (value) = (min);   \
        }                      \
    } while (0)

#endif
