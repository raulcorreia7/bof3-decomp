#include "battle_15.h"

MATCH void func_800A1B38(void) {
    u8 battler;

    if (func_800A3C9C(g_BattleActiveBattler, g_BattleTarget) == 0) {
        battler = LOBU(g_BattleTarget);
        if (BATTLER_IS_PLAYER(battler)) {
            g_BattleTargetRecord->hp_change = g_Game.members[battler].chr.hp;
        } else {
            g_BattleTargetRecord->hp_change = ENEMY_COMBATANT(battler).hp;
        }
    }
}
