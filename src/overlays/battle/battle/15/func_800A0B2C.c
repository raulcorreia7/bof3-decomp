#include "battle_15.h"

MATCH void func_800A0B2C(void) {
    u8          battler;
    u16         base;
    BattleTurn* record;

    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        battler = LOBU(g_Battle.target);
        if (BATTLER_IS_PLAYER(battler)) {
            base = g_Game.members[battler].chr.hp;
        } else {
            base = ENEMY_COMBATANT(battler).hp;
        }
        if (base == 1u) {
            g_Battle.target_record->hp_change = 0;
            return;
        }
        record                                    = *(BattleTurn**)&g_Battle.target_record;
        /* FAKE: volatile-drop cell read keeps the decrement ahead of the pointer
         * load, as the shipped code orders them. */
        ((volatile BattleTurn*)record)->hp_change = (base - 1);
    }
}
