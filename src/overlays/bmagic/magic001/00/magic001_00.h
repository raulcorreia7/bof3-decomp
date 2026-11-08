#ifndef OVERLAY_BMAGIC_MAGIC001_00_H
#define OVERLAY_BMAGIC_MAGIC001_00_H

/* The bmagic/magic001/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8               g_BattleActiveBattler;
extern EffectStepFuncs3 D_801EEC3C;

static inline void BMagic_ClearWorkFlagsAndStep(void) {
    if (g_Task->param.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
        g_Task->header.mode += 1;
    }
}

#endif
