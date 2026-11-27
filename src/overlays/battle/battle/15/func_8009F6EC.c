#include "battle_15.h"

MATCH void func_8009F6EC(void) {
    volatile u16* flags;
    s16           result;
    u16           flag_value;
    u32           battler_index;

    flags      = &g_BattleState;
    flag_value = *flags;
    D_801EC2EE = 0;
    /* FAKE: the block holds these two stores in place. */
    do {
        *flags        = flag_value | BATTLE_STATE_DAMAGE_APPLIED;
        battler_index = g_BattleActiveBattler;
    } while (0);
    result                            = Battle_CalcDamage(battler_index, g_Battle.target, BATTLE_ELEMENT_FROM_WEAPON);
    g_Battle.target_record->hp_change = (result * 2);
    g_GameBonebreakTimer.hours        = 5;
}
