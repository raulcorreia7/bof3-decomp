#ifndef OVERLAY_BMAGIC_MAGIC001_00_H
#define OVERLAY_BMAGIC_MAGIC001_00_H

/* The bmagic/magic001/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleHandlerTable3 D_801EEC3C;
extern u8                  g_BattleActingBattler;

void func_800AFC54(void);
void func_801E257C(u32 enemy_index, u32 script_index);

static inline void BMagic_ClearWorkFlagsAndStep(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        g_SpadWork->step_01 += 1;
    }
}

#endif
