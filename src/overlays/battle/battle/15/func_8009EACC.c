#include "battle_15.h"

MATCH void func_8009EACC(void) {
    volatile u16* flags;
    s16           result;
    u32           new_var;

    flags = &g_BattleState;
    /* FAKE: the block holds these two stores in place. */
    do {
        *flags |= BATTLE_STATE_DAMAGE_APPLIED;
        new_var = g_BattleActiveBattler;
    } while (0);
    result                            = Battle_CalcDamage(new_var, g_Battle.target, BATTLE_ELEMENT_FROM_WEAPON);
    g_Battle.target_record->hp_change = (result >> 1) + 1;
}
