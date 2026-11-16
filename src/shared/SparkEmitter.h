#ifndef SHARED_SPARK_EMITTER_H
#define SHARED_SPARK_EMITTER_H

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

#endif
