#include "battle_15.h"

/* Non-volatile view of the battler selection index (0x80146394): battle_15.h
 * declares it volatile, whose byte load cannot feed the index arithmetic
 * without an extra mask. */

MATCH void func_8009DBA4(void) {
    u32 index;
    u16 base;
    s16 value;

    ((s16*)g_BattleTargetRecord)[2] = Battle_CalcDamage(g_BattleActiveBattler, g_BattleTarget, 4);
    /* FAKE: holds the selection-record store ahead of the index reload. */
    MATCH_FAKE_BARRIER();
    index = (*(u8*)&g_BattleTarget);
    if (index < 3u) {
        base = g_BattlePartyBattlers[index].chr.hp;
    } else {
        base = ENEMY_COMBATANT(index).hp;
    }
    value = ((s16*)g_BattleTargetRecord)[2];
    if ((value < (s32)base) && (value != 0)) {
        func_800A4238(4);
    }
}
