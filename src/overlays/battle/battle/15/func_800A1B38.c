#include "battle_15.h"

MATCH void func_800A1B38(void) {
    u8 battler;

    if (func_800A3C9C(g_Battle.active_battler, g_Battle.target) == 0) {
        battler = LOBU(g_Battle.target);
        if (BATTLER_IS_PLAYER(battler)) {
            g_Battle.target_record->hp_change = g_Game.members[battler].chr.hp;
        } else {
            g_Battle.target_record->hp_change = ENEMY_COMBATANT(battler).hp;
        }
    }
}
