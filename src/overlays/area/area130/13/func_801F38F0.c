#include "area130_13.h"

MATCH void func_801F38F0(void) {
    SpawnedActor* slot;
    Actor*        work;
    u8            index;

    index = Actor_FindFreeSpawned();
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x78;
        work               = SELF(Actor);
        WorldPos_Copy(&slot->pos, &work->pos);
    }
}
