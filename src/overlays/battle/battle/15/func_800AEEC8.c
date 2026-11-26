#include "battle_15.h"

/* Queues a 0x48 effect for the current task with the given mode, or mode 8 when the target check fails. */
MATCH void func_800AEEC8(s32 effect_mode, u8 target_slot) {
    u8 mode;
    u8 selector;
    u8 slot;
    mode = effect_mode;
    slot = target_slot;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        selector = D_800B6BF0[effect_mode & 3];
        slot     = target_slot + 3;
    } else {
        selector = D_800B6BF0[effect_mode & 3];
    }
    if ((u8)Battle_CanTarget(selector, slot) == 0) {
        mode = 8;
    }
    slot                               = Battle_AllocEffect(1, 0x48);
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    g_BattleEffects[slot].unk_04       = mode;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].unk_0A       = 0;
}
