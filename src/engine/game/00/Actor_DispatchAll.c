#include "game_00.h"

MATCH void Actor_DispatchAll(void) {
    s32        count;
    ActorSlot* slot;

    count = 0;
    do {
        if (g_ActorSlots[count & 0xFF].header.flags != 0) {
            slot = &g_ActorSlots[count & 0xFF];
            TASK_SET(slot);
            g_ActorHandlers[slot->type]();
        }
        count++;
    } while ((u32)(count & 0xFF) < ACTOR_SLOT_COUNT);
}
