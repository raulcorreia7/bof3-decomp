#include "game_00.h"

MATCH void Actor_DispatchAll(void) {
    s32           count;
    SpawnedActor* slot;

    count = 0;
    do {
        if (g_SpawnedActors[count & BYTE_MASK].header.flags != 0) {
            slot = &g_SpawnedActors[count & BYTE_MASK];
            TASK_SET(slot);
            g_ActorTypes[slot->type]();
        }
        count++;
    } while ((u32)(count & BYTE_MASK) < ACTOR_SLOT_COUNT);
}
