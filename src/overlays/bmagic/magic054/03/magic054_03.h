#ifndef OVERLAY_BMAGIC_MAGIC054_03_H
#define OVERLAY_BMAGIC_MAGIC054_03_H

/* The bmagic/magic054/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC054_STEP_COUNT 4

typedef struct Magic054Steps {
    Callback steps[MAGIC054_STEP_COUNT];
} Magic054Steps;

/* The queued effect rows (stride 0x78) this target spawns into. */
extern BattleEffect      D_801EC330[];
extern Magic054Steps     D_801EEC04;
extern BMagicEffectSteps D_801EEC14;

void func_800A9610(u8 target_mask, u16 damage_flags);
u8   func_801DB524(u32 slot);
u32  func_801E590C(u32 mode, u32 effect_type);

#endif
