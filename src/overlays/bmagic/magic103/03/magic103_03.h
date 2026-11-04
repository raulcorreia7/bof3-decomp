#ifndef OVERLAY_BMAGIC_MAGIC103_03_H
#define OVERLAY_BMAGIC_MAGIC103_03_H

/* The bmagic/magic103/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* One offset row the effect adds to the selected actor's position (x, y, z). */
typedef struct BmagicOffset {
    s32 x;
    s32 y;
    s32 z;
} BmagicOffset;

ASSERT_SIZE(BmagicOffset, 0xC);
ASSERT_OFFSET(BmagicOffset, x, 0x0);
ASSERT_OFFSET(BmagicOffset, y, 0x4);
ASSERT_OFFSET(BmagicOffset, z, 0x8);

extern BmagicOffset D_801F07AC[];
extern Callback     D_801F07C4[];
void                func_801EFE20(void);

extern Callback D_801F07D4[];
void            func_801F04E0(void);

extern Callback D_801F07A0[];
void            func_801EF1D8(void);

#endif
