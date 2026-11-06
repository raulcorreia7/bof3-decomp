#ifndef COMMON_FIXED_H
#define COMMON_FIXED_H

#include "types.h"

/* A 16.16 fixed-point coordinate: the whole word, or the fraction and integer
 * halves the world code reads alone. */
typedef union Coord {
    s32 fixed;

    struct {
        u16 fraction;
        s16 integer;
    } part;
} Coord;

ASSERT_SIZE(Coord, 0x04);

/* The integer and fraction halves of a Coord, as lvalues: `COORD_INT(pos.z) -= 0x40;`. */
#define COORD_INT(c)  ((c).part.integer)
#define COORD_FRAC(c) ((c).part.fraction)

#endif
