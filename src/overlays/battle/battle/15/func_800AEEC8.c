#include "battle_15.h"

/* 3 differing: +0x80 loads 1 before g_SpadWork; move the work load ahead of the queue writes. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_800AEEC8(s32 arg0, u8 arg1, s32 arg2) {
    u8  mode;
    u8  selector;
    u8  slot;
    s32 status;
    mode = arg0;
    slot = arg1;
    if (g_BattleTargetSelector & BATTLE_TARGET_ENEMY_SIDE) {
        selector = D_800B6BF0[arg0 & 3];
        slot     = arg1 + 3;
    } else {
        selector = D_800B6BF0[arg0 & 3];
    }
    status = func_800AED5C(selector, slot);
    if ((u8)status == 0) {
        mode = 8;
    }
    slot                               = Battle_AllocEffect(1, 0x48);
    g_BattleEffects[slot].unk_04       = mode;
    g_BattleEffects[slot].unk_09       = 1;
    g_BattleEffects[slot].unk_0A       = 0;
    g_BattleEffects[slot].target.party = g_SpadWork;
    return 1;
}
#else
INCLUDE_ASM(func_800AEEC8);
#endif
