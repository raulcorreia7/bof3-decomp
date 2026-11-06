#include "battle_15.h"

MATCH void func_800A0244(void) {
    u8  battler;
    u16 base;

    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
        battler = LOBU(g_BattleTarget);
        if (BATTLER_IS_PLAYER(battler)) {
            base = g_BattlePartyBattlers[battler].chr.hp;
        } else {
            base = ENEMY_COMBATANT(battler).hp;
        }
        g_BattleTargetRecord->hp_change = (base >> 1);
    }
}
