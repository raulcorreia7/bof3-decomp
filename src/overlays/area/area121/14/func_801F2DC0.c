#include "area121_14.h"

MATCH void func_801F2DC0(void) {
    s32        actor_slot;
    SpawnedActor* slot;

    actor_slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (actor_slot == GAME_NONE) {
        return;
    }
    slot               = &g_SpawnedActors[actor_slot];
    slot->header.flags = 1;
    slot->type         = 0xBA;
}
