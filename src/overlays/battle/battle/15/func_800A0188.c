#include "battle_15.h"

MATCH void func_800A0188(void) {
    BattleTurn* record;
    u8          mode;
    u16         base;

    g_Battle.target_record->hp_change =
        Battle_CalcDamage(g_Battle.active_battler, g_Battle.target, BATTLE_ELEMENT_FROM_WEAPON);
    /* FAKE: barrier holds mode load below the store */
    FAKE_BARRIER();
    mode = LOBU(g_Battle.target);
    if (mode < 3u) {
        base = g_Game.members[mode].chr.hp;
    } else {
        base = ENEMY_COMBATANT(mode).hp;
    }
    record = *(BattleTurn**)&g_Battle.target_record;
    if (record->hp_change >= (s16)base) {
        record->hp_change = (base - 1);
    }
}
