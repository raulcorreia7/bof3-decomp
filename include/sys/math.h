#ifndef SYSTEM_MATH_H
#define SYSTEM_MATH_H

#include "types.h"

/* 4096 is 1.0 and one turn; angles use the same unit. PsyQ <libgte.h> also
 * defines ONE with the same value. */
#ifndef ONE
#define ONE 4096
#endif

/* Fixed-point multiply by 1.0 (ONE): two ONE-scaled values, result ONE-scaled. */
#define FIXED_MUL(a, b) (((a) * (b)) >> 12)

/* One turn of the fixed-point angle unit. */
#define ANGLE_MASK      (ONE - 1)

/* Whole-degree angles in the 4096-unit turn; ONE is the full turn. */
#define ANGLE_45        (ONE / 8)

/* A degree count converted to the 4096-unit angle at run time. */
#define DEG(degrees)    ((degrees) * ONE / 360)

/* In-place integer lower bound. Standard statement macro: trailing semicolon
 * required. It bounds a stable lvalue in place and keeps the retail
 * comparison, spelling, signedness and read order, so an argument that reads
 * memory or a volatile keeps its original repeated-read behavior. The bound
 * must be side-effect free.
 *
 *   CLAMP_MIN(value, min);   raises value to at least min
 *
 * No upper-bound companion: its two sites keep their explicit branch
 * (world00/area027/13 func_801F2F0C).
 */
#define CLAMP_MIN(value, min)  \
    do {                       \
        if ((value) < (min)) { \
            (value) = (min);   \
        }                      \
    } while (0)

#endif
