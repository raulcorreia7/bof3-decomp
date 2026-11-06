#include "battle_15.h"

/* Non-volatile view of the selected battler index (0x80146374): battle_15.h
 * declares it volatile, whose byte load cannot feed the index arithmetic
 * without an extra mask. */

/* FAKE: the call arguments are read into locals first and the barrier keeps the
 * 0xFFFF materialization out of the load-delay path, so it lands in the jal
 * delay slot as retail has it.
 */
MATCH void func_8009F010(void) {
    /* FAKE: retail keeps the enemy row index in v0. */
    MATCH_REG(s32, enemy_index, "v0");
    u8  index;
    u16 value;
    u8  battler_index;
    u8  selection_kind;
    s16 selection;

    index = LOBU(g_BattleActiveBattler);
    if (index < 3) {
        value = g_BattlePartyBattlers[index].chr.stats.intellect;
    } else {
        enemy_index = index - 3;
        value       = g_BattleEnemyBattlers[enemy_index].stats.intellect;
    }
    D_801EC30C     = value;
    battler_index  = g_BattleActiveBattler;
    selection_kind = g_BattleTarget;
    /* FAKE: keeps the 0xFFFF load in the jal delay slot. */
    MATCH_FAKE_BARRIER();
    selection                       = Battle_CalcDamage(battler_index, selection_kind, 0xFFFF);
    ((s16*)g_BattleTargetRecord)[2] = selection;
}
