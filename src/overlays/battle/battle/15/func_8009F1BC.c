#include "battle_15.h"

/* FAKE: the call arguments are read into locals first and the barrier keeps the
 * kind-0x20 materialization out of the load-delay path, so it lands in the jal
 * delay slot as retail has it.
 */
MATCH void func_8009F1BC(void) {
    u8  battler;
    u16 value;
    u8  battler_index;
    u8  selection_kind;
    s16 res;

    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        value = g_BattlePartyBattlers[battler].chr.stats.power * 2;
    } else {
        value = ENEMY_COMBATANT(battler).stats.power * 2;
    }
    D_801EC30C     = value;
    battler_index  = g_BattleActiveBattler;
    selection_kind = g_BattleTarget;
    /* FAKE: keeps the kind-0x20 materialization in the jal delay slot. */
    MATCH_FAKE_BARRIER();
    res                             = Battle_CalcDamage(battler_index, selection_kind, 0x20);
    ((s16*)g_BattleTargetRecord)[2] = res;
}
