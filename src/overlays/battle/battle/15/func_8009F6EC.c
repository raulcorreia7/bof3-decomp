#include "battle_15.h"

MATCH void func_8009F6EC(void) {
    volatile u16* flags;
    s16           result;
    u16           flag_value;
    u32           battler_index;

    flags      = &g_BattleState;
    flag_value = *flags;
    D_801EC2EE = 0;
    /* FAKE: ORDER_LOCK is the macro spelling of the do/while (0) block that keeps this statement in place. */
    ORDER_LOCK(*flags = flag_value | BATTLE_STATE_DAMAGE_APPLIED; battler_index = g_BattleActiveBattler);
    result                        = Battle_CalcDamage(battler_index, g_BattleTarget, 0xFFFF);
    g_BattleTargetRecord[2]       = (s16)((s32)result * 2);
    g_GameBonebreakTimer.hours_00 = 5;
}
