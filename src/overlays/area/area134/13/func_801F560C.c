#include "area134_13.h"

MATCH void func_801F560C(void) {
    SpawnedActor* slot;
    Actor*        work;
    u8            index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x93;
        work               = g_Task;
        WorldPos_Copy(&slot->pos, &work->pos);
    }
}
