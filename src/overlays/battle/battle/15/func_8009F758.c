#include "battle_15.h"

MATCH void func_8009F758(void) {
    if (g_Battle.action_type == BATTLE_ACTION_ABILITY && g_Battle.action_id == ABILITY_MIGHTY_CHOP) {
        g_Battle.flags |= BATTLE_STATE_DAMAGE_APPLIED;
    }
    *(s16*)&D_801EC2EE                = 0;
    g_Battle.target_record->hp_change = (Battle_CalcDamage(g_Battle.active_battler, g_Battle.target, BATTLE_ELEMENT_FROM_WEAPON) / 4);
}
