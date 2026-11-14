#include "area132_13.h"

MATCH void func_801F3C1C(void) {
    s32        actor_slot;
    SpawnedActor* slot;

    actor_slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (actor_slot == GAME_NONE) {
        return;
    }
    slot               = &g_SpawnedActors[actor_slot];
    slot->header.flags = 1;
    slot->type         = 0x74;
    slot->pos.x.fixed  = TO_COORD(43);
    slot->pos.y.fixed  = TO_COORD(40);
    slot->pos.z.fixed  = Area_SampleHeight(slot->pos.x.fixed, TO_COORD(40)) << 16;
}
