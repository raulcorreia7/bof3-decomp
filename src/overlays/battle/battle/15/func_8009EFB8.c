#include "battle_15.h"

MATCH void func_8009EFB8(void) {
    u16 index;
    u8  battler_index;
    u16 mask;
    u8  selection_kind;

    index                             = g_Battle.action_id;
    battler_index                     = g_Battle.active_battler;
    mask                              = D_801CA71C[index].mask & ELEM_ALL;
    selection_kind                    = g_Battle.target;
    g_Battle.target_record->hp_change = Battle_CalcDamage(battler_index, selection_kind, mask);
}
