#include "area119_13.h"

MATCH void func_801F3B98(void) {
    u8 index;

    if (g_AreaSceneMode == 0) {
        Actor_Clear();
        return;
    }
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        return;
    }
    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        g_ActorSlots[index].header.flags = 1;
        g_ActorSlots[index].type         = 0x18;
        g_ActorSlots[index].header.mode  = 0x58;
        g_ActorSlots[index].header.step  = 0;
        g_ActorSlots[index].pos.x.fixed  = D_801F4614[g_Task->param.unk_0B].x << 12;
        g_ActorSlots[index].pos.y.fixed  = D_801F4614[g_Task->param.unk_0B].y << 12;
        g_Task->timer                    = RANDOM_MASK(15) + 20;
        g_Task->param.unk_0B             = (g_Task->param.unk_0B + 1) & 0x7;
    }
}
