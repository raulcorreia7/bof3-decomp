#ifndef AREA_EFFECTS_H
#define AREA_EFFECTS_H

/* The work records of the area effects the area and scenario overlays share: sparks, the spin effect and the motion trail. */

#include "common/vector.h"
#include "area/area.h"
#include "psx/psyq.h"

/* One of the 128 falling sparks at AREA_WORK: the walkers fall it by its speed each frame and clear it below the actor's ground height. */
typedef struct AreaSpark {
    u8     active;     /* 0x00 - 0 marks a free spark */
    u8     unk_01;     /* 0x01 */
    s16    fall_speed; /* 0x02 - 16.8 fall per frame */
    VECTOR pos;        /* 0x04 */
} AreaSpark;

#define AREA_SPARK_COUNT 128

/* The four bytes every spark table slot starts with. */
typedef struct EffectSlotHeader {
    u8 active; /* 0 marks a free slot */
    u8 type;   /* selects the per-frame handler */
    u8 life;   /* frames left */
    u8 shade;  /* the spark's color level, faded or added each frame */
} EffectSlotHeader;

ASSERT_SIZE(EffectSlotHeader, 4);

/* One spark of a scene effect table: type selects the per-frame handler. Used by the
 * area098 table (16 slots at AREA_WORK, 0x1C bytes each) and the scena07 and scena08 tables. */
typedef struct FallingSpark {
    EffectSlotHeader header;
    u8               life_reload; /* 0x04 - frames loaded into life when it runs out */
    u8               pad_05[3];
    s32              speed; /* 0x08 - vertical speed */
    VECTOR           pos;   /* 0x0C */
} FallingSpark;

ASSERT_OFFSET(FallingSpark, life_reload, 0x04);
ASSERT_OFFSET(FallingSpark, speed, 0x08);
ASSERT_OFFSET(FallingSpark, pos, 0x0C);
ASSERT_SIZE(FallingSpark, 0x1C);

ASSERT_OFFSET(AreaSpark, active, 0x00);
ASSERT_OFFSET(AreaSpark, unk_01, 0x01);
ASSERT_OFFSET(AreaSpark, fall_speed, 0x02);
ASSERT_OFFSET(AreaSpark, pos, 0x04);
ASSERT_SIZE(AreaSpark, 0x14);

/* One 0x14-byte emitter of the table at AREA_WORK + 0x1800: it spawns two sparks each time its timer runs out. */
typedef struct SparkEmitter {
    u8     active; /* +0x00 */
    u8     unk_01; /* +0x01 */
    u8     unk_02; /* +0x02 */
    u8     timer;  /* +0x03 */
    VECTOR pos;    /* +0x04 */
} SparkEmitter;

/* One 0x18-byte row of the sprite work table at AREA_WORK. */
typedef struct SpriteSpark {
    u8     active;  /* +0x00 */
    u8     unk_01;  /* +0x01 */
    u8     life;    /* +0x02 */
    u8     blink;   /* +0x03 - per-frame colour phase: the draw is grey when set, red otherwise */
    VECTOR pos;     /* +0x04 */
    s32    z_delta; /* +0x14 - rises by 0x20000 per update and is added to z */
} SpriteSpark;

/* The sprite work table at AREA_WORK holds this many SpriteSpark rows. */
#define SPRITE_SPARK_COUNT 256

ASSERT_SIZE(SparkEmitter, 0x14);
ASSERT_SIZE(SpriteSpark, 0x18);
ASSERT_OFFSET(SparkEmitter, timer, 0x03);
ASSERT_OFFSET(SpriteSpark, z_delta, 0x14);

#define g_SparkEmitters ((SparkEmitter*)(AREA_WORK + 0x1800))

/* The spin-effect work record the overlay's sprite pass draws. */
typedef struct SpinEffect {
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
} SpinEffect;

ASSERT_OFFSET(SpinEffect, origin, 0x00);
ASSERT_OFFSET(SpinEffect, vertex_a, 0x10);
ASSERT_OFFSET(SpinEffect, vertex_b, 0x18);
ASSERT_OFFSET(SpinEffect, spin_angle, 0x24);
ASSERT_OFFSET(SpinEffect, scale, 0x28);
ASSERT_OFFSET(SpinEffect, fade, 0x2A);
ASSERT_SIZE(SpinEffect, 0x2C);

/* One point of a trail: a world position and where it lands on the screen. */
typedef struct TrailPoint {
    VECTOR pos;    /* the task position when the point was taken */
    Pos2   screen; /* pos projected to the screen */
    s16    angle;  /* the heading the trail has at this point */
    s16    width;  /* the projected width */
} TrailPoint;

ASSERT_OFFSET(TrailPoint, screen, 0x10);
ASSERT_OFFSET(TrailPoint, angle, 0x14);
ASSERT_SIZE(TrailPoint, 0x18);

#define TRAIL_LENGTH        32
#define TRAIL_HEADING_UNSET 0x1000

/* The record of the last 32 positions the glowing ribbon behind a moving object is drawn from. */
typedef struct Trail {
    TrailPoint point[TRAIL_LENGTH];
    u16        heading[TRAIL_LENGTH - 1]; /* screen heading from each point to the next */
    u16        width;                     /* the world width every point projects */
} Trail;

ASSERT_OFFSET(Trail, heading, 0x300);
ASSERT_SIZE(Trail, 0x340);

/* A falling spark particle: the area and scenario spark tables (area197 at AREA_WORK,
 * scena09 at AREA_WORK + 0x800) fall it by its velocity, bounce it off the ground and
 * fade it while its life runs. */
typedef struct SparkParticle {
    EffectSlotHeader header;
    u8               frame; /* 0x04 - indexes the draw routine's corner table */
    u8               pad_05[3];
    VECTOR           velocity; /* 0x08 */
    VECTOR           pos;      /* 0x18 */
} SparkParticle;

ASSERT_OFFSET(SparkParticle, velocity, 0x08);
ASSERT_OFFSET(SparkParticle, pos, 0x18);
ASSERT_SIZE(SparkParticle, 0x28);

/* The second and third vertex of a spark triangle relative to its projected first vertex, in screen space. */
typedef struct TriangleOffset {
    u16 dx1;
    u16 dy1;
    u16 dx2;
    u16 dy2;
} TriangleOffset;

ASSERT_OFFSET(TriangleOffset, dy1, 0x02);
ASSERT_OFFSET(TriangleOffset, dx2, 0x04);
ASSERT_OFFSET(TriangleOffset, dy2, 0x06);
ASSERT_SIZE(TriangleOffset, 8);

/* One 10-byte point of a dot trail (area098 at AREA_WORK + 0x2000, sce15ef1 at AREA_WORK + 0x5A00). */
typedef struct TrailDot {
    u8  active; /* 0x00 - flips every frame it is processed */
    u8  life;   /* 0x01 */
    u16 color;  /* 0x02 - 5-5-5 */
    s16 x;      /* 0x04 */
    s16 y;      /* 0x06 */
    s8  dx;     /* 0x08 */
    s8  dy;     /* 0x09 */
} TrailDot;

ASSERT_SIZE(TrailDot, 10);

#endif
