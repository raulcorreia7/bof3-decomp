#ifndef COMMON_FIXED_H
#define COMMON_FIXED_H

#include "types.h"

/* A 16.16 fixed-point coordinate: the whole word, or the fraction and integer halves the world code reads alone. */
typedef union Coord {
    s32 fixed;

    struct {
        u16 fraction;
        s16 integer;
    } part;
} Coord;

ASSERT_SIZE(Coord, 0x04);

/* The integer and fraction halves of a Coord, as lvalues: `COORD_INT(pos.z) -= 0x40;`. */
#define COORD_INT(c)     ((c).part.integer)
#define COORD_FRAC(c)    ((c).part.fraction)

/* The integer part and the low 16 bits of a whole 16.16 word, as values: `FIX_INT(pos.z.fixed)`. */
#define FIX_INT(x)       ((x) >> 16)
#define FIX_FRAC(x)      ((x) & 0xFFFF)

/* A whole number of cells as a 16.16 coordinate: `TO_COORD(12) + COORD_HALF` is 12.5. */
#define TO_COORD(n)      ((n) << 16)
#define COORD_HALF       0x8000

/* A whole number of cells plus a half: `TO_COORD_HALF(1)` is 1.5. */
#define TO_COORD_HALF(n) (TO_COORD(n) + COORD_HALF)

#endif
