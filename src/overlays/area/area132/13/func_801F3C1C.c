#include "area132_13.h"

MATCH void func_801F3C1C(void) {
    s32        actor_slot;
    ActorSlot* slot;

    actor_slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (actor_slot == GAME_NONE) {
        return;
    }
    slot               = &g_ActorSlots[actor_slot];
    slot->header.flags = 1;
    slot->type         = 0x74;
    slot->x.fixed      = 0x2B0000;
    slot->y.fixed      = 0x280000;
    slot->z.fixed      = Area_SampleHeight(slot->x.fixed, 0x280000) << 16;
}
