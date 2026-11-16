#ifndef OVERLAY_BMAGIC_MAGIC116_03_H
#define OVERLAY_BMAGIC_MAGIC116_03_H

/* The bmagic/magic116/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect*       D_801EC2E0;
extern Magic010SharedSteps D_801EEC04;

/* Draws every live streak segment and moves it one frame; returns 1 while any
 * segment is live. */
u8 func_801EF118(void);

/* One segment of the streak pool at D_801EF2A8: two points that fall together
 * and the colour at each end of the ribbon they draw. */
typedef struct BMagicStreakSegment {
    /* 0x00 */ u8        active;
    /* 0x01 */ u8        unk_01;
    /* 0x02 */ u8        life;
    /* 0x03 */ u8        pad_03;
    /* 0x04 */ Pos3      head;
    /* 0x10 */ u8        pad_10[4];
    /* 0x14 */ Pos3      tail;
    /* 0x20 */ u8        pad_20[4];
    /* 0x24 */ Pos3      velocity;
    /* 0x30 */ u8        pad_30[4];
    /* 0x34 */ ColorRGB8 head_color;
    /* 0x37 */ u8        pad_37;
    /* 0x38 */ ColorRGB8 tail_color;
    /* 0x3B */ u8        pad_3B;
} BMagicStreakSegment;

ASSERT_OFFSET(BMagicStreakSegment, life, 0x02);
ASSERT_OFFSET(BMagicStreakSegment, head, 0x04);
ASSERT_OFFSET(BMagicStreakSegment, tail, 0x14);
ASSERT_OFFSET(BMagicStreakSegment, velocity, 0x24);
ASSERT_OFFSET(BMagicStreakSegment, head_color, 0x34);
ASSERT_OFFSET(BMagicStreakSegment, tail_color, 0x38);
ASSERT_SIZE(BMagicStreakSegment, 0x3C);

extern BMagicStreakSegment D_801EF2A8[];

BMagicStreakSegment* func_801EEFB8(void);
void                 func_801EF020(BMagicStreakSegment* record);
void                 func_801AFE18(void);

#endif
