#include "battle_15.h"

MATCH void func_800AE108(s32 battler_index, s32 work_ptr) {
    s32           linked_slot;
    s32           work_cell;
    s32           queued_slot;
    u8            slot_index;
    volatile u16* active_index;

    work_cell     = work_ptr;
    slot_index    = battler_index;
    active_index  = &g_BattleActionId;
    *active_index = slot_index & BYTE_MASK;
    queued_slot   = Battle_AllocEffect(2, D_800B6510[slot_index & BYTE_MASK]) & BYTE_MASK;
    g_BattleEffects[queued_slot].work_74.address = work_cell;
    if (D_801CA71C[*active_index].mask & 0x1000) {
        linked_slot                                 = Battle_AllocEffect(1, 0x43U) & BYTE_MASK;
        g_BattleEffects[linked_slot].work_74.effect = &g_BattleEffects[queued_slot];
        g_BattleEffects[linked_slot].unk_0B         = slot_index;
    }
}
