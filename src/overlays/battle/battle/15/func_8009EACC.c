#include "battle_15.h"

MATCH void func_8009EACC(void) {
    volatile u16* flags;
    s16           result;
    u32           new_var;

    flags = &g_BattleState;
    /* FAKE: the order lock holds these two stores in place. */
    ORDER_LOCK_BEGIN
        *flags |= BATTLE_STATE_DAMAGE_APPLIED;
        new_var = g_BattleActiveBattler;
    ORDER_LOCK_END;
    result                          = Battle_CalcDamage(new_var, g_BattleTarget, BATTLE_ELEMENT_FROM_WEAPON);
    g_BattleTargetRecord->hp_change = (result >> 1) + 1;
}
