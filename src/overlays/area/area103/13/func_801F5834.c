#include "area103_13.h"

MATCH void func_801F5834(void) {
    s32 slot = Actor_FindFreeSlot() & BYTE_MASK;

    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].type         = 0x4D;
        g_ActorSlots[slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_ActorSlots[slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_ActorSlots[slot].pos.z.fixed  = g_Task->pos.z.fixed;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
