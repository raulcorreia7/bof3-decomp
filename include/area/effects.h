#ifndef AREA_EFFECTS_H
#define AREA_EFFECTS_H

/* The work records of the area effects the area and scenario overlays share: sparks, the spin effect and the chain. */

#include "common/vector.h"
#include "area/area.h"
#include "psx/psyq.h"

/* One of the 128 falling sparks at AREA_WORK: the walkers fall it by its speed
 * each frame and clear it below the actor's ground height. */
typedef struct AreaSpark {
    u8   active;     /* 0x00 - 0 marks a free spark */
    u8   unk_01;     /* 0x01 */
    s16  fall_speed; /* 0x02 - 16.8 fall per frame */
    Pos3 pos;        /* 0x04 */
    s32  unk_10;     /* 0x10 */
} AreaSpark;

#define AREA_SPARK_COUNT 128

ASSERT_SIZE(AreaSpark, 0x14);
ASSERT_OFFSET(AreaSpark, active, 0x00);
ASSERT_OFFSET(AreaSpark, unk_01, 0x01);
ASSERT_OFFSET(AreaSpark, fall_speed, 0x02);
ASSERT_OFFSET(AreaSpark, pos, 0x04);
ASSERT_OFFSET(AreaSpark, unk_10, 0x10);

/* One 0x14-byte emitter of the table at AREA_WORK + 0x1800: it spawns two sparks each time its timer runs out. */
typedef struct SparkEmitter {
    u8  active; /* +0x00 */
    u8  unk_1;  /* +0x01 */
    u8  unk_2;  /* +0x02 */
    u8  timer;  /* +0x03 */
    s32 x;      /* +0x04 */
    s32 y;      /* +0x08 */
    s32 z;      /* +0x0C */
    s32 unk_10; /* +0x10 */
} SparkEmitter;

/* One 0x18-byte row of the sprite work table at AREA_WORK. */
typedef struct SpriteSpark {
    u8  active; /* +0x00 */
    u8  unk_1;  /* +0x01 */
    u8  life;   /* +0x02 */
    u8  blink;  /* +0x03 - per-frame colour phase: the draw is grey when set, red otherwise */
    s32 x;      /* +0x04 */
    s32 y;      /* +0x08 */
    s32 z;      /* +0x0C */
    s32 unk_10; /* +0x10 */
    s32 z_step; /* +0x14 - rises by 0x20000 per update and is added to z */
} SpriteSpark;

/* The sprite work table at AREA_WORK holds this many SpriteSpark rows. */
#define SPRITE_SPARK_COUNT 256

ASSERT_SIZE(SparkEmitter, 0x14);
ASSERT_SIZE(SpriteSpark, 0x18);
ASSERT_OFFSET(SparkEmitter, timer, 0x03);
ASSERT_OFFSET(SpriteSpark, z_step, 0x14);

#define g_SparkEmitters ((SparkEmitter*)(AREA_WORK + 0x1800))

/* The spin-effect work record the overlay's sprite pass draws. */
typedef struct WorldSpin {
    Pos3               origin;
    u8                 unk_0C[4];
    /* 0x10 */ SVECTOR vertex_a;   /* the first rotated vertex offset */
    /* 0x18 */ SVECTOR vertex_b;   /* the second rotated vertex offset */
    /* 0x20 */ s16     angle_lo;   /* the angle accumulator's low half */
    /* 0x22 */ s16     angle_hi;   /* the angle accumulator's high half */
    /* 0x24 */ s16     spin_angle; /* the spin angle */
    s16                unk_26;
    /* 0x28 */ s16     scale; /* the vertex scale */
    /* 0x2A */ s16     fade;  /* the triangle fade */
} WorldSpin;

ASSERT_SIZE(WorldSpin, 0x2C);
ASSERT_OFFSET(WorldSpin, origin, 0x00);
ASSERT_OFFSET(WorldSpin, vertex_a, 0x10);
ASSERT_OFFSET(WorldSpin, vertex_b, 0x18);
ASSERT_OFFSET(WorldSpin, spin_angle, 0x24);
ASSERT_OFFSET(WorldSpin, scale, 0x28);
ASSERT_OFFSET(WorldSpin, fade, 0x2A);

/* A chain of 32 screen-projected points with the direction between neighbours. */
typedef struct ChainNode {
    s32 pos[3];
    u8  pad_0C[4];
    s16 screen[2];
    s16 angle;
    s16 size;
} ChainNode;

typedef struct Chain {
    ChainNode node[32];
    u16       dir[31];
    u16       size;
} Chain;

#endif
