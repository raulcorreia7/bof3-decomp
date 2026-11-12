#ifndef OVERLAY_BMAGIC_MAGIC116_03_H
#define OVERLAY_BMAGIC_MAGIC116_03_H

/* The bmagic/magic116/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect*       D_801EC2E0;
extern Magic010SharedSteps D_801EEC04;

/* The guard the record reset waits on, the battle flag it raises, and the
 * request hand-off that follows. */
u8 func_801EF118(void);

/* One quad of the effect: two world points, a color and a shared speed. */
typedef struct Magic116Quad {
    /* 0x00 */ u8       state;
    /* 0x01 */ u8       unk_01;
    /* 0x02 */ u8       timer;
    /* 0x03 */ u8       pad_03;
    /* 0x04 */ WorldPos pos;
    /* 0x10 */ u8       pad_10[4];
    /* 0x14 */ WorldPos unk_14;
    /* 0x20 */ u8       pad_20[4];
    /* 0x24 */ Coord3D  speed;
    /* 0x30 */ u8       pad_30[4];
    /* 0x34 */ u8       color[3];
    /* 0x37 */ u8       pad_37;
    /* 0x38 */ u8       unk_38[3];
    /* 0x3B */ u8       pad_3B;
} Magic116Quad;

ASSERT_SIZE(Magic116Quad, 0x3C);
ASSERT_OFFSET(Magic116Quad, timer, 0x02);
ASSERT_OFFSET(Magic116Quad, pos, 0x04);
ASSERT_OFFSET(Magic116Quad, unk_14, 0x14);
ASSERT_OFFSET(Magic116Quad, speed, 0x24);
ASSERT_OFFSET(Magic116Quad, color, 0x34);
ASSERT_OFFSET(Magic116Quad, unk_38, 0x38);

extern Magic116Quad D_801EF2A8[128];

Magic116Quad* func_801EEFB8(void);
void          func_801EF020(Magic116Quad* record);

#endif
