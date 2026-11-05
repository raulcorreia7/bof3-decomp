#ifndef OVERLAY_BMAGIC_MAGIC001_00_H
#define OVERLAY_BMAGIC_MAGIC001_00_H

/* The bmagic/magic001/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleHandlerTable3 D_801EEC3C;
extern u8                  g_BattleActiveBattler;

void func_800AFC54(void);
void func_801E257C(u32 enemy_index, u32 script_index);

static inline void BMagic_ClearWorkFlagsAndStep(void) {
    if (g_Task->unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
        g_Task->mode += 1;
    }
}

#endif
