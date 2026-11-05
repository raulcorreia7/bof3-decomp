#include "battle_15.h"

MATCH void func_8009EACC(void) {
    volatile u16* flags;
    s16           result;
    u32           new_var;

    flags = &g_BattleState;
    /* FAKE: ORDER_LOCK is the macro spelling of the do/while (0) block that keeps this statement in place. */
    ORDER_LOCK(*flags |= BATTLE_STATE_DAMAGE_APPLIED; new_var = g_BattleActiveBattler);
    result                          = Battle_CalcDamage(new_var, g_BattleTarget, 0xFFFF);
    ((s16*)g_BattleTargetRecord)[2] = (result >> 1) + 1;
}
