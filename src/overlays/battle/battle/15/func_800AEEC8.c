#include "battle_15.h"

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
    g_BattleEffects[slot].arg.unk_09   = status;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].unk_0A       = 0;
    return status;
}
#else
INCLUDE_ASM(func_800AEEC8);
#endif
