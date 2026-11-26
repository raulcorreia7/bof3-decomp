#include "area103_13.h"

MATCH void func_801F5834(void) {
    s32 slot = Actor_FindFreeSpawned() & BYTE_MASK;

    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0x4D;
        g_SpawnedActors[slot].pos.x.fixed  = SELF(Actor)->pos.x.fixed;
        g_SpawnedActors[slot].pos.y.fixed  = SELF(Actor)->pos.y.fixed;
        g_SpawnedActors[slot].pos.z.fixed  = SELF(Actor)->pos.z.fixed;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
