#include "area052_13.h"

MATCH void func_801F4290(void) {
    s32           actor_slot;
    SpawnedActor* slot;

    actor_slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (actor_slot == GAME_NONE) {
        return;
    }
    slot               = &g_SpawnedActors[actor_slot];
    slot->header.flags = 1;
    slot->type         = 0x48;
    slot->pos.x.fixed  = TO_COORD(136);
    slot->pos.y.fixed  = TO_COORD(17);
    /* kept: retail reads the sampled height as an int, with no halfword extension. */
    {
        Coord sample_x = {slot->pos.x.fixed};
        Coord sample_y = {TO_COORD(17)};

        slot->pos.z.fixed = ((s32 (*)(s32, s32))Area_HeightSample)(sample_x.fixed, sample_y.fixed) << 8;
    }
    slot->link = 8;
}
