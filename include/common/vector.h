#ifndef COMMON_VECTOR_H
#define COMMON_VECTOR_H

#include "types.h"

/* Packed vectors used across images; PsyQ vectors retain their SDK padding. */
typedef struct Vec2s {
    s16 x;
    s16 y;
} Vec2s;

typedef struct Vec2us {
    u16 x;
    u16 y;
} Vec2us;

typedef struct Vec2i {
    s32 x;
    s32 y;
} Vec2i;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

/* Three signed words: a position or an angle accumulator that the game stores
 * packed, without the SDK's pad word. */
typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

ASSERT_SIZE(Vec2s, 0x04);
ASSERT_SIZE(Vec2us, 0x04);
ASSERT_SIZE(Vec2i, 0x08);
ASSERT_SIZE(Vec3s, 0x06);
ASSERT_SIZE(Vec3i, 0x0C);

/* Texture coordinates are four packed bytes. */
typedef struct TexRect {
    u8 u0;
    u8 v0;
    u8 u1;
    u8 v1;
} TexRect;

ASSERT_SIZE(TexRect, 0x04);

typedef s32 Fixed;
typedef s32 Fixed12;
typedef s16 Angle;

ASSERT_SIZE(Fixed, 0x04);
ASSERT_SIZE(Fixed12, 0x04);
ASSERT_SIZE(Angle, 0x02);

/* A 16.16 fixed-point coordinate: the whole word, or the fraction and integer
 * halves the world code reads alone (tasks/names-ram/ram-map.tsv names the
 * words at +0x34, +0x38 and +0x3C x, y and z). */
typedef union Coord {
    s32 fixed;

    struct {
        u16 fraction;
        s16 integer;
    } part;
} Coord;

ASSERT_SIZE(Coord, 0x04);

/* The integer and fraction halves of a Coord, as lvalues. */
#define COORD_INT(c)  (c).part.integer
#define COORD_FRAC(c) (c).part.fraction

#endif
