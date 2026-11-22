#include "area175_13.h"

MATCH void func_801F431C(void) {
    SpawnedActor* slot;
    s32           index;

    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x39;
        slot->screen_x     = TASK(Actor)->screen_x;
        slot->screen_y     = TASK(Actor)->screen_y;
    }
}
