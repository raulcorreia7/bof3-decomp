#include "game_00.h"

MATCH void Actor_DispatchAll(void) {
    s32        count;
    ActorSlot* slot;

    count = 0;
    do {
        if (g_ActorSlots[count & BYTE_MASK].flags_00 != 0) {
            slot       = &g_ActorSlots[count & BYTE_MASK];
            g_SpadWork = (Actor*)slot;
            g_ActorHandlers[slot->type]();
        }
        count++;
    } while ((u32)(count & BYTE_MASK) < ACTOR_SLOT_COUNT);
}
