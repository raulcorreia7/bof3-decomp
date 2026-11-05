#include "battle_15.h"

MATCH void func_8009EB28(void) {
    volatile u16* flagp;
    volatile u8*  battlerp;
    volatile u16* scaledp;
    u16           flag;
    u32           battler;
    u16           base;
    /* FAKE: retail keeps the loaded scaled halfword in v0. */
    MATCH_REG(s32, scaled, "v0");
    /* FAKE: retail keeps the shift result in v1. */
    MATCH_REG(s32, shifted, "v1");
    u8  battler_check;
    u8  selection;
    u32 enemy;
    s16 value;

    flagp   = &g_BattleState;
    flag    = *flagp;
    battler = (*(u8*)&g_BattleActiveBattler);
    *flagp  = flag | BATTLE_STATE_DAMAGE_APPLIED;
    if (BATTLER_IS_PLAYER(battler)) {
        base = D_80145F18[battler][6];
    } else {
        /* FAKE: retail computes the enemy row index in v0, the row offset in v1. */
        MATCH_REG(u32, enemy, "v0") = battler - 3;
        base                        = D_801EB6C4[enemy][8];
    }
    D_801EC30C = base;
    /* FAKE: retail stores the scaled base before materialising the next addresses. */
    MATCH_FAKE_BARRIER();
    battlerp                        = &g_BattleActiveBattler;
    battler_check                   = *battlerp;
    scaledp                         = &D_801EC30C;
    scaled                          = *scaledp;
    shifted                         = scaled >> 2;
    selection                       = g_BattleTarget;
    *scaledp                        = scaled + shifted;
    value                           = Battle_CalcDamage(battler_check, selection, 0xFFFF);
    ((s16*)g_BattleTargetRecord)[2] = value;
    if (value != 0 && (func_800A3A10(*battlerp, g_BattleTarget) & BYTE_MASK) == 0) {
        func_801DDFEC(g_BattleTarget);
        func_801DD14C(g_BattleTarget);
    }
}
