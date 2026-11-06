#include "battle_15.h"

extern u8 D_801CA71B[];

MATCH void func_800A1AD0(void) {
    u16 index;

    g_BattleTargetRecord->target_flags = 2;
    /* FAKE: ORDER_LOCK keeps this statement in place; without it the match is 88.89%. */
    ORDER_LOCK(index = g_BattleActionId;);
    g_BattleTargetRecord->ap_change =
        func_800A2880(g_BattleActiveBattler, *(u8*)(void*)&g_BattleTarget, D_801CA71B[index * 0x14], 1);
}
