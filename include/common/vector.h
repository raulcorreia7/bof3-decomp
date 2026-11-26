#ifndef COMMON_VECTOR_H
#define COMMON_VECTOR_H

#include "common/fixed.h"
#include "psyq/libgte.h"
#include "types.h"

/* Packed vectors shared across images, named by what they hold; PsyQ vectors keep their SDK padding. */

/* A map cell's column and row. */
typedef struct Cell2 {
    u8 x;
    u8 y;
} Cell2;

/* A screen or map position: the SDK's 2-D short vector. */
typedef DVECTOR Pos2;

/* A position stored unsigned. */
typedef struct Pos2u {
    u16 x;
    u16 y;
} Pos2u;

/* A whole-unit offset or nudge on each axis. */
typedef struct Offset2 {
    s32 x;
    s32 y;
} Offset2;

/* The step one move takes on each axis, one byte wide; a table of them is indexed by direction. */
typedef struct Step2 {
    s8 dx;
    s8 dy;
} Step2;

/* A 3-D point stored packed in halfwords. */
typedef struct Pos3s {
    s16 x;
    s16 y;
    s16 z;
} Pos3s;

/* A 3-D position in whole units, packed without the SDK's pad word. */
typedef struct Pos3 {
    s32 x;
    s32 y;
    s32 z;
} Pos3;

/* A 16.16 pair. */
typedef struct Coord2 {
    Coord x;
    Coord y;
} Coord2;

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
typedef Offset2 SpriteScale;

/* A rotation accumulator per axis, in whole units. */
typedef Pos3 Angle3;

/* One red, green and blue level a byte wide, without the SDK's fourth byte; CVECTOR is the padded form. */
typedef struct ColorRGB8 {
    u8 r;
    u8 g;
    u8 b;
} ColorRGB8;

/* Signed per-channel colour shift of a palette fade; each channel is added to the colours it fades. */
typedef struct ColorDelta8 {
    s8 r;
    s8 g;
    s8 b;
} ColorDelta8;

/* One red, green and blue level a halfword wide. */
typedef struct ColorRGB16 {
    u16 r;
    u16 g;
    u16 b;
} ColorRGB16;

ASSERT_SIZE(Coord3, 0x0C);
ASSERT_OFFSET(Coord3, x, 0x00);
ASSERT_OFFSET(Coord3, y, 0x04);
ASSERT_OFFSET(Coord3, z, 0x08);

ASSERT_SIZE(Cell2, 0x02);
ASSERT_SIZE(Coord2, 0x08);
ASSERT_SIZE(Pos2, 0x04);
ASSERT_OFFSET(Pos2, vy, 0x02);
ASSERT_SIZE(Pos2u, 0x04);
ASSERT_OFFSET(Pos2u, y, 0x02);
ASSERT_SIZE(Offset2, 0x08);
ASSERT_OFFSET(Offset2, y, 0x04);
ASSERT_SIZE(Step2, 0x02);
ASSERT_SIZE(Pos3s, 0x06);
ASSERT_SIZE(Pos3, 0x0C);
ASSERT_OFFSET(Pos3, y, 0x04);
ASSERT_OFFSET(Pos3, z, 0x08);
ASSERT_SIZE(ColorRGB8, 0x03);
ASSERT_OFFSET(ColorRGB8, b, 0x02);
ASSERT_SIZE(ColorDelta8, 0x03);
ASSERT_OFFSET(ColorDelta8, b, 0x02);
ASSERT_SIZE(ColorRGB16, 0x06);
ASSERT_OFFSET(ColorRGB16, b, 0x04);

#endif
