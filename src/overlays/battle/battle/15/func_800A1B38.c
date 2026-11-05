#include "battle_15.h"

MATCH void func_800A1B38(void) {
    u8 battler;

    if (func_800A3C9C(g_BattleActiveBattler, g_BattleTarget) == 0) {
        battler = LOBU(g_BattleTarget);
        if (BATTLER_IS_PLAYER(battler)) {
            ((s16*)g_BattleTargetRecord)[2] = (s16)g_BattlePartyBattlers[battler].chr.hp;
        } else {
            ((s16*)g_BattleTargetRecord)[2] = (s16)ENEMY_COMBATANT(battler).hp;
        }
    }
}
