#include "battle_15.h"

MATCH void func_800A0188(void) {
    s16* record;
    u8   mode;
    u16  base;

    g_BattleTargetRecord[2] = Battle_CalcDamage(g_BattleActiveBattler, g_BattleTarget, 0xFFFF);
    /* FAKE: barrier holds mode load below the store */
    MATCH_FAKE_BARRIER();
    mode = LOBU(g_BattleTarget);
    if (mode < 3u) {
        base = g_BattlePartyBattlers[mode].chr.hp;
    } else {
        base = ENEMY_COMBATANT(mode).hp;
    }
    record = *(s16**)&g_BattleTargetRecord;
    if (record[2] >= (s16)base) {
        record[2] = (s16)(base - 1);
    }
}
