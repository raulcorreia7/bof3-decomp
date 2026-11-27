#include "area034_13.h"

MATCH void func_801F2D1C(void) {
    SpawnedActor* slot;
    u8            index;

    SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();
    index                         = SELF(Actor)->param.actor_slot;
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x51;
        slot->header.mode  = 6;
        slot->pos.x.fixed  = TO_COORD(54);
        slot->pos.y.fixed  = TO_COORD(66);
        slot->pos.z.fixed  = Area_HeightSample(slot->pos.x.fixed, TO_COORD(66)) << 0x10;
    }
}
