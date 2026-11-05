#include "area103_13.h"

MATCH void func_801F5834(void) {
    s32 slot = func_8019601C() & 0xFF;

    if (slot != 0xFF) {
        g_ActorSlots[slot].flags_00 = 1;
        g_ActorSlots[slot].type     = 0x4D;
        g_ActorSlots[slot].x.fixed  = g_SpadWork->x.fixed;
        g_ActorSlots[slot].y.fixed  = g_SpadWork->y.fixed;
        g_ActorSlots[slot].z.fixed  = g_SpadWork->z.fixed;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
