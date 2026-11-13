#include "battle_15.h"

extern u8 D_801CA71B[];

MATCH void func_800A1AD0(void) {
    u16 index;

    g_Battle.target_record->target_flags = 2;
    /* FAKE: FAKE_ORDER_LOCK keeps this statement in place; without it the match is 88.89%. */
    FAKE_ORDER_LOCK(index = g_BattleActionId;);
    g_Battle.target_record->ap_change = Battle_GetActionId(g_BattleActiveBattler, *(u8*)(void*)&g_Battle.target, D_801CA71B[index * 0x14], 1);
}
