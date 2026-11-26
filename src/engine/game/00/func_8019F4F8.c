#include "game_00.h"

MATCH void func_8019F4F8(void) {
    u8  timer;
    s32 step;
    s32 active;
    s32 routeOffset;

    timer = TASK(Actor)->timer;
    if (timer != 0) {
        timer--;
        TASK(Actor)->timer = timer;
        step               = TASK(Actor)->vy + 0x14000;
        active             = (s32)(g_FrameCount & 0x1u);
        TASK(Actor)->pos.y.fixed += step;
        TASK(Actor)->vy = step;
        if (active != 0) {
            routeOffset = (s32)TASK(Actor)->param.party_index * BATTLE_PARTY_STRIDE;
            Actor_DrawValueDigits(*(s16*)(((u8*)&g_Game.members[0].screen_x) + routeOffset), (s16)(*(u16*)(((u8*)&g_Game.members[0].screen_y) + routeOffset) + (u16)COORD_INT(TASK(Actor)->pos.y)),
                                  TASK(Actor)->unk_06, TASK(Actor)->clut_select);
        }
    } else {
        Actor_Clear();
    }
}
