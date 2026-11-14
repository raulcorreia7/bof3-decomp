#ifndef COMMON_VECTOR_H
#define COMMON_VECTOR_H

#include "common/fixed.h"
#include "types.h"

/* Packed vectors used across images; PsyQ vectors retain their SDK padding. */
typedef struct Point2s {
    s16 x;
    s16 y;
} Point2s;

typedef struct Point2u {
    u16 x;
    u16 y;
} Point2u;

typedef struct Point2l {
    s32 x;
    s32 y;
} Point2l;

/* A signed step on each axis, one byte wide. */
typedef struct Offset2b {
    s8 dx;
    s8 dy;
} Offset2b;

typedef struct Point3s {
    s16 x;
    s16 y;
    s16 z;
} Point3s;

/* Three signed words: a position or an angle accumulator that the game stores
 * packed, without the SDK's pad word. */
typedef struct Point3l {
    s32 x;
    s32 y;
    s32 z;
} Point3l;

typedef struct Coord3 {
    Coord x;
    Coord y;
    Coord z;
} Coord3;

/* Where an actor or effect stands: x, y and z in 16.16 world units. */
typedef Coord3 WorldPos;

/* Move `dst` to where `src` stands, one axis at a time. */
static inline void WorldPos_Copy(WorldPos* dst, WorldPos* src) {
    dst->x.fixed = src->x.fixed;
    dst->y.fixed = src->y.fixed;
    dst->z.fixed = src->z.fixed;
}

/* A sprite's horizontal and vertical size, 16.16; 0x10000 is full size. */
typedef Point2l SpriteScale;

ASSERT_SIZE(Coord3, 0x0C);
ASSERT_OFFSET(Coord3, x, 0x00);
ASSERT_OFFSET(Coord3, y, 0x04);
ASSERT_OFFSET(Coord3, z, 0x08);

ASSERT_SIZE(Point2s, 0x04);
ASSERT_OFFSET(Point2s, y, 0x02);
ASSERT_SIZE(Point2u, 0x04);
ASSERT_OFFSET(Point2u, y, 0x02);
ASSERT_SIZE(Point2l, 0x08);
ASSERT_OFFSET(Point2l, y, 0x04);
ASSERT_SIZE(Offset2b, 0x02);
ASSERT_SIZE(Point3s, 0x06);
ASSERT_SIZE(Point3l, 0x0C);
ASSERT_OFFSET(Point3l, y, 0x04);
ASSERT_OFFSET(Point3l, z, 0x08);

#endif
