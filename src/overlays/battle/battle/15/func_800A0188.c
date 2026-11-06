#include "battle_15.h"

MATCH void func_800A0188(void) {
    BattleTurn* record;
    u8          mode;
    u16         base;

    g_BattleTargetRecord->hp_change =
        Battle_CalcDamage(g_BattleActiveBattler, g_BattleTarget, BATTLE_ELEMENT_FROM_WEAPON);
    /* FAKE: barrier holds mode load below the store */
    MATCH_FAKE_BARRIER();
    mode = LOBU(g_BattleTarget);
    if (mode < 3u) {
        base = g_BattlePartyBattlers[mode].chr.hp;
    } else {
        base = ENEMY_COMBATANT(mode).hp;
    }
    record = *(BattleTurn**)&g_BattleTargetRecord;
    if (record->hp_change >= (s16)base) {
        record->hp_change = (base - 1);
    }
}
