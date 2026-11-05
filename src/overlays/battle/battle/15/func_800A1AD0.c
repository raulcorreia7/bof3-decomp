#include "battle_15.h"

extern u8 D_801CA71B[];

MATCH void func_800A1AD0(void) {
    u16 index;

    ((volatile u8*)g_BattleTargetRecord)[8] = 2;
    /* FAKE: ORDER_LOCK keeps this statement in place; without it the match is 88.89%. */
    ORDER_LOCK(index = g_BattleActionId;);
    *((s16*)(((u8*)g_BattleTargetRecord) + 6)) =
        func_800A2880(g_BattleActiveBattler, *(u8*)(void*)&g_BattleTarget, D_801CA71B[index * 0x14], 1);
}
