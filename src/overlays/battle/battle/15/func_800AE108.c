#include "battle_15.h"

MATCH void func_800AE108(s32 battler_index, s32 work_ptr) {
    s32           linked_slot;
    s32           work_cell;
    s32           queued_slot;
    u8            action_id;
    volatile u16* active_index;

    work_cell                                   = work_ptr;
    action_id                                   = battler_index;
    active_index                                = &g_Battle.action_id;
    *active_index                               = action_id & BYTE_MASK;
    queued_slot                                 = Battle_AllocEffect(2, g_BattleActionSelection[action_id & BYTE_MASK]) & BYTE_MASK;
    g_BattleEffects[queued_slot].target.address = work_cell;
    if (D_801CA71C[*active_index].mask & 0x1000) {
        linked_slot                                = Battle_AllocEffect(1, 67U) & BYTE_MASK;
        g_BattleEffects[linked_slot].target.effect = &g_BattleEffects[queued_slot];
        g_BattleEffects[linked_slot].unk_0B        = action_id;
    }
}
