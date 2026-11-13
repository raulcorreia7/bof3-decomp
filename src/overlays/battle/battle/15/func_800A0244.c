#include "battle_15.h"

MATCH void func_800A0244(void) {
    u8  battler;
    u16 base;

    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        battler = LOBU(g_Battle.target);
        if (BATTLER_IS_PLAYER(battler)) {
            base = g_Game.members[battler].chr.hp;
        } else {
            base = ENEMY_COMBATANT(battler).hp;
        }
        g_Battle.target_record->hp_change = (base >> 1);
    }
}
