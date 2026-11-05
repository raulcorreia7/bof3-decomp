#include "game_00.h"

MATCH void func_8019F4F8(void) {
    u8  timer;
    s32 step;
    s32 active;
    s32 routeOffset;

    timer = g_Task->unk_09;
    if (timer != 0) {
        timer--;
        g_Task->unk_09 = timer;
        step           = g_Task->vy + 0x14000;
        active         = (s32)(g_FrameCount & 1u);
        g_Task->y.fixed += step;
        g_Task->vy = step;
        if (active != 0) {
            routeOffset = (s32)g_Task->unk_0B * BATTLE_PARTY_STRIDE;
            func_8019F5B8(
                *(s16*)(((u8*)&g_BattlePartyBattlers[0].unk_2E) + routeOffset),
                (s16)(*(u16*)(((u8*)&g_BattlePartyBattlers[0].unk_30) + routeOffset) + (u16)COORD_INT(g_Task->y)),
                g_Task->unk_06, g_Task->unk_27);
        }
    } else {
        Actor_Clear();
    }
}
