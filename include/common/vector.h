#ifndef COMMON_VECTOR_H
#define COMMON_VECTOR_H

#include "common/fixed.h"
#include "types.h"

/* Packed vectors used across images; PsyQ vectors retain their SDK padding. */
typedef struct Vec2S16 {
    s16 x;
    s16 y;
} Vec2S16;

typedef struct Vec2U16 {
    u16 x;
    u16 y;
} Vec2U16;

typedef struct Vec2S32 {
    s32 x;
    s32 y;
} Vec2S32;

typedef struct Vec3S16 {
    s16 x;
    s16 y;
    s16 z;
} Vec3S16;

/* Three signed words: a position or an angle accumulator that the game stores
 * packed, without the SDK's pad word. */
typedef struct Vec3S32 {
    s32 x;
    s32 y;
    s32 z;
} Vec3S32;

typedef struct Vec3Coord {
    Coord x;
    Coord y;
    Coord z;
} Vec3Coord;

/* Where an actor or effect stands: x, y and z in 16.16 world units. */
typedef Vec3Coord WorldPos;

/* A sprite's horizontal and vertical size, 16.16; 0x10000 is full size. */
typedef Vec2S32 SpriteScale;

ASSERT_SIZE(Vec3Coord, 0x0C);
ASSERT_OFFSET(Vec3Coord, x, 0x00);
ASSERT_OFFSET(Vec3Coord, y, 0x04);
ASSERT_OFFSET(Vec3Coord, z, 0x08);

ASSERT_SIZE(Vec2S16, 0x04);
ASSERT_SIZE(Vec2U16, 0x04);
ASSERT_SIZE(Vec2S32, 0x08);
ASSERT_SIZE(Vec3S16, 0x06);
ASSERT_SIZE(Vec3S32, 0x0C);

#endif
