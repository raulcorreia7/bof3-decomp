#include "battle_15.h"

MATCH void func_8009F758(void) {
    if (*(u8*)&g_BattleActionType == BATTLE_ACTION_ABILITY && *(u16*)&g_BattleActionId == 0x9A) {
        g_BattleState |= BATTLE_STATE_DAMAGE_APPLIED;
    }
    *(s16*)&D_801EC2EE              = 0;
    ((s16*)g_BattleTargetRecord)[2] = (s16)(Battle_CalcDamage(g_BattleActiveBattler, g_BattleTarget, 0xFFFF) / 4);
}
