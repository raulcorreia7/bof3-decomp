#include "battle_15.h"

MATCH void func_800A0B2C(void) {
    u8   battler;
    u16  base;
    s16* record;

    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
        battler = LOBU(g_BattleTarget);
        if (BATTLER_IS_PLAYER(battler)) {
            base = g_BattlePartyBattlers[battler].stats.current_hp;
        } else {
            base = ENEMY_COMBATANT(battler).hp;
        }
        if (base == 1u) {
            ((s16*)g_BattleTargetRecord)[2] = 0;
            return;
        }
        record                     = *(s16**)&g_BattleTargetRecord;
        /* FAKE: volatile-drop cell read keeps the decrement ahead of the pointer
         * load, as the shipped code orders them. */
        ((volatile s16*)record)[2] = (s16)(base - 1);
    }
}
