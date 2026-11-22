#include "area188_13.h"

MATCH void func_801F4B24(void) {
    s32           slot;
    SpawnedActor* spawned_actor;

    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        spawned_actor               = &g_SpawnedActors[slot];
        spawned_actor->header.flags = 1;
        spawned_actor->type         = 0xB9;
    }
}
