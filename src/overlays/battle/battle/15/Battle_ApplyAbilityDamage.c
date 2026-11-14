#include "battle_15.h"

extern u8 D_801CA71B[];

/* func_8009DCC8 */
MATCH void Battle_ApplyAbilityDamage(void) {
    s32 index;
    u8  battler_index;
    u8  selection_kind;
    u8  base_value;

    index                             = g_Battle.action_id;
    battler_index                     = *(u8*)(void*)&g_Battle.active_battler;
    selection_kind                    = *(u8*)(void*)&g_Battle.target;
    base_value                        = D_801CA71B[4 * (5 * index)];
    g_Battle.target_record->hp_change = Battle_GetActionId(battler_index, selection_kind, base_value, 0);
}
