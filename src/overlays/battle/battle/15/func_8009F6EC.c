#include "battle_15.h"

MATCH void func_8009F6EC(void) {
    volatile u16* flags;
    s16           result;
    u16           flag_value;
    u32           battler_index;

    flags      = &g_BattleState;
    flag_value = *flags;
    D_801EC2EE = 0;
    /* FAKE: the order lock holds these two stores in place. */
    FAKE_ORDER_LOCK_BEGIN
        *flags        = flag_value | BATTLE_STATE_DAMAGE_APPLIED;
        battler_index = g_BattleActiveBattler;
    FAKE_ORDER_LOCK_END;
    result                            = Battle_CalcDamage(battler_index, g_Battle.target, BATTLE_ELEMENT_FROM_WEAPON);
    g_Battle.target_record->hp_change = (result * 2);
    g_GameBonebreakTimer.hours        = 5;
}
