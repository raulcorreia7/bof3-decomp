#ifndef OVERLAY_BMAGIC_MAGIC116_03_H
#define OVERLAY_BMAGIC_MAGIC116_03_H

/* The bmagic/magic116/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect*       D_801EC2E0;
extern Magic010SharedSteps D_801EEC04;

/* The guard the record reset waits on, the battle flag it raises, and the
 * request hand-off that follows. */
u8 func_801EF118(void);

/* One segment of the streak pool at D_801EF2A8: two points that fall together
 * and the colour at each end of the ribbon they draw. */
typedef struct BMagicStreakSegment {
    /* 0x00 */ u8       active;
    /* 0x01 */ u8       unk_01;
    /* 0x02 */ u8       life;
    /* 0x03 */ u8       pad_03;
    /* 0x04 */ Point3DL head;
    /* 0x10 */ u8       pad_10[4];
    /* 0x14 */ Point3DL tail;
    /* 0x20 */ u8       pad_20[4];
    /* 0x24 */ Point3DL velocity;
    /* 0x30 */ u8       pad_30[4];
    /* 0x34 */ u8  head_red;
    /* 0x35 */ u8  head_green;
    /* 0x36 */ u8  head_blue;
    /* 0x37 */ u8  pad_37;
    /* 0x38 */ u8  tail_red;
    /* 0x39 */ u8  tail_green;
    /* 0x3A */ u8  tail_blue;
    /* 0x3B */ u8  pad_3B;
} BMagicStreakSegment;

ASSERT_SIZE(BMagicStreakSegment, 0x3C);
ASSERT_OFFSET(BMagicStreakSegment, life, 0x02);
ASSERT_OFFSET(BMagicStreakSegment, head, 0x04);
ASSERT_OFFSET(BMagicStreakSegment, tail, 0x14);
ASSERT_OFFSET(BMagicStreakSegment, velocity, 0x24);
ASSERT_OFFSET(BMagicStreakSegment, head_red, 0x34);
ASSERT_OFFSET(BMagicStreakSegment, tail_red, 0x38);

extern BMagicStreakSegment D_801EF2A8[];

void func_801EF020(BMagicStreakSegment* segment);

#endif
