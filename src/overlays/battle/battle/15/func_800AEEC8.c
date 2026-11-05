#include "battle_15.h"

/* blocker: tail regalloc; first diff: +0x80 `li v0,1` where retail reads g_SpadWork.
 * Reordering the stores or hoisting work/result locals keeps 3 differ and +4 bytes, moving
 * the first diff to +0x70 (`andi a0,v0,0xff` against retail `andi v0,v0,0xff`); the draft
 * already returns the stored 1. Permuter 115k iterations, best score 480. */
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
