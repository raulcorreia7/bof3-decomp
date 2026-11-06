#include "area103_13.h"

MATCH void func_801F5834(void) {
    s32 slot = Actor_FindFreeSlot() & 0xFF;

    if (slot != 0xFF) {
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].type         = 0x4D;
        g_ActorSlots[slot].x.fixed      = g_Task->x.fixed;
        g_ActorSlots[slot].y.fixed      = g_Task->y.fixed;
        g_ActorSlots[slot].z.fixed      = g_Task->z.fixed;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
