#include "area052_13.h"

MATCH void func_801F431C(void) {
    s32           actor_slot;
    SpawnedActor* slot;
    /* FAKE: the retail frame holds 16 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 16);

    actor_slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (actor_slot == GAME_NONE) {
        return;
    }
    slot               = &g_SpawnedActors[actor_slot];
    slot->header.flags = 1;
    slot->pos.x.fixed  = TO_COORD(137);
    slot->type         = 0x48;
    slot->pos.y.fixed  = TO_COORD(17) + COORD_HALF;
    /* kept: retail reads the sampled height as an int, with no halfword extension. */
    slot->pos.z.fixed  = ((s32 (*)(s32, s32))Area_SampleHeight)(slot->pos.x.fixed, TO_COORD(17) + COORD_HALF) << 8;
    slot->link         = 16;
}
