#include "game_00.h"

MATCH void func_8019F4F8(void) {
    u8  timer;
    s32 step;
    s32 active;
    s32 routeOffset;

    timer = g_Task->timer;
    if (timer != 0) {
        timer--;
        g_Task->timer = timer;
        step          = g_Task->vy + 0x14000;
        active        = (s32)(g_FrameCount & 0x1u);
        g_Task->pos.y.fixed += step;
        g_Task->vy = step;
        if (active != 0) {
            routeOffset = (s32)g_Task->param.party_index * BATTLE_PARTY_STRIDE;
            func_8019F5B8(*(s16*)(((u8*)&g_Game.members[0].unk_2E) + routeOffset), (s16)(*(u16*)(((u8*)&g_Game.members[0].unk_30) + routeOffset) + (u16)COORD_INT(g_Task->pos.y)), g_Task->unk_06,
                          g_Task->unk_27);
        }
    } else {
        Actor_Clear();
    }
}
