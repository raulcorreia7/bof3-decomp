#include "area103_13.h"

MATCH void func_801F5834(void) {
    s32 slot = Actor_FindFreeSlot() & BYTE_MASK;

    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0x4D;
        g_SpawnedActors[slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_SpawnedActors[slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_SpawnedActors[slot].pos.z.fixed  = g_Task->pos.z.fixed;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
