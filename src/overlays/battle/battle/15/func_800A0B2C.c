#include "battle_15.h"

MATCH void func_800A0B2C(void) {
    u8          battler;
    u16         base;
    BattleTurn* record;

    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
        battler = LOBU(g_BattleTarget);
        if (BATTLER_IS_PLAYER(battler)) {
            base = g_BattlePartyBattlers[battler].chr.hp;
        } else {
            base = ENEMY_COMBATANT(battler).hp;
        }
        if (base == 1u) {
            g_BattleTargetRecord->hp_change = 0;
            return;
        }
        record                                    = *(BattleTurn**)&g_BattleTargetRecord;
        /* FAKE: volatile-drop cell read keeps the decrement ahead of the pointer
         * load, as the shipped code orders them. */
        ((volatile BattleTurn*)record)->hp_change = (base - 1);
    }
}
