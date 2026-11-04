#include "game_00.h"

MATCH u8 Actor_FindFreeSlot() {
    u8 i;

    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if (g_ActorSlots[i].flags_00 == 0) {
            return i;
        }
    }
    return 0xFF;
}
