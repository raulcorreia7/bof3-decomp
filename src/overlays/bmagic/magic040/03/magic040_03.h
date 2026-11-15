#ifndef OVERLAY_BMAGIC_MAGIC040_03_H
#define OVERLAY_BMAGIC_MAGIC040_03_H

/* The bmagic/magic040/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC040_STEP_COUNT 4

typedef struct Magic040Steps {
    Callback steps[MAGIC040_STEP_COUNT];
} Magic040Steps;

extern Magic040Steps D_801EEC10;
extern Point2s       D_801EFC74[][2];
extern Point2s       D_801EFCCC[][2];
extern u8            D_801EFD24[];

/* The columns of the effect table the step fills: its type byte, two step bytes and its target. */
extern BattleEffectByteColumn   D_801EC334[];
extern BattleEffectByteColumn   D_801EC339[];
extern BattleEffectByteColumn   D_801EC33A[];
extern BattleEffectTargetColumn D_801EC3A4[];

u8 func_800AED5C(s32 selector, u32 battler_index);

void func_801EF430(void* task);
void func_801EF600(u8 start, u16 radius);

#endif
