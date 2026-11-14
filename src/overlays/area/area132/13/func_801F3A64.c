#include "area132_13.h"

MATCH void func_801F3A64(void) {
    SpawnedActor* actor;
    s32        slot;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        actor               = &g_SpawnedActors[slot];
        actor->header.flags = 1;
        actor->type         = 0x73;
        actor->pos.x.fixed  = TO_COORD(42);
        actor->header.mode  = 0;
        actor->pos.y.fixed  = TO_COORD(29);
        actor->pos.z.fixed  = Area_SampleHeight(actor->pos.x.fixed, TO_COORD(29)) << 0x10;
    }
}
