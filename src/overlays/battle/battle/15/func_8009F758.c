#include "battle_15.h"

MATCH void func_8009F758(void) {
    if (*(u8*)&g_BattleActionType == BATTLE_ACTION_ABILITY && *(u16*)&g_BattleActionId == ABILITY_MIGHTY_CHOP) {
        g_BattleState |= BATTLE_STATE_DAMAGE_APPLIED;
    }
    *(s16*)&D_801EC2EE = 0;
    g_BattleTargetRecord->hp_change =
        (Battle_CalcDamage(g_BattleActiveBattler, g_BattleTarget, BATTLE_ELEMENT_FROM_WEAPON) / 4);
}
