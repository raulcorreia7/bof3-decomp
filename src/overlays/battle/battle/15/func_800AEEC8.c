#include "battle_15.h"

/* nonmatching: 9 rows differ, one scheduling difference. Retail loads g_Task (lui/lw a0) before `li v0,1` and the
 * stores; ours loads it after the unk_04 and unk_09 stores (first row 0x800AEF48). Tried: status local for the 1,
 * g_Task in a local before or after the alloc, the target store first (both move the offset into a0 and break the
 * prologue), 115k permuter iterations. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_800AEEC8(s32 arg0, u8 arg1) {
    u8  mode;
    u8  selector;
    u8  slot;
    s32 status;
    mode = arg0;
    slot = arg1;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
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
    status                             = 1;
    g_BattleEffects[slot].unk_04       = mode;
    g_BattleEffects[slot].unk_09       = status;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].unk_0A       = 0;
    return status;
}
#else
INCLUDE_ASM(func_800AEEC8);
#endif
