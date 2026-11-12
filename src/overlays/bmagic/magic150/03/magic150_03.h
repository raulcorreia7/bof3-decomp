#ifndef OVERLAY_BMAGIC_MAGIC150_03_H
#define OVERLAY_BMAGIC_MAGIC150_03_H

/* The bmagic/magic150/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EEC04[];

/* One sparkle the eye beam draws: its live flag, its offset along the beam,
 * its angle and the frames it has left. */
typedef struct Magic150Spark {
    u16 active; /* 0x00 */
    s16 offset; /* 0x02 */
    u16 angle;  /* 0x04 */
    s16 life;   /* 0x06 */
} Magic150Spark;

ASSERT_SIZE(Magic150Spark, 0x08);
ASSERT_OFFSET(Magic150Spark, active, 0x00);
ASSERT_OFFSET(Magic150Spark, offset, 0x02);
ASSERT_OFFSET(Magic150Spark, angle, 0x04);
ASSERT_OFFSET(Magic150Spark, life, 0x06);

/* The beam origin, the radii that fan it and the eight sparks the cursor walks. */
typedef struct Magic150Sparks {
    s32           origin[3]; /* 0x00 */
    u8            pad_0C[4];
    s16           radius; /* 0x10 */
    s16           unk_12; /* 0x12 */
    u16           unk_14; /* 0x14 */
    u8            pad_16[2];
    Magic150Spark sparks[8]; /* 0x18 */
} Magic150Sparks;

ASSERT_SIZE(Magic150Sparks, 0x58);
ASSERT_OFFSET(Magic150Sparks, origin, 0x00);
ASSERT_OFFSET(Magic150Sparks, radius, 0x10);
ASSERT_OFFSET(Magic150Sparks, unk_12, 0x12);
ASSERT_OFFSET(Magic150Sparks, unk_14, 0x14);
ASSERT_OFFSET(Magic150Sparks, sparks, 0x18);
extern Magic150Sparks D_801EFA9C;
/* The cursor over the spark table. */
extern Magic150Spark* D_801EFAF4;

/* A world point and the screen cells its left, centre and right projections land in. */
typedef struct ProjectedSpan {
    s32     pos[3];
    u8      pad_0C[4];
    DVECTOR screen[3]; /* 0x10 left, 0x14 centre, 0x18 right */
} ProjectedSpan;

void func_801EF254(void);
u8   func_801EF8EC(void);
/* func_801EF2C0 */
void BMagic_ProjectSpan(ProjectedSpan* span);

void func_801AFE18(void);
void func_801EF040(void);
void func_801EF6F8(void);
void func_801EF790(s16 x, s16 y, s16 radius, u8 color, u8 edge_color);

#endif
