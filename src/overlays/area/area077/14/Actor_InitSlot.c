#include "area077_14.h"

/* func_801F61F0 */
MATCH void Actor_InitSlot(s32 type) {
    ActorSlot* record;
    u8         slot;

    slot = Actor_FindFreeSlot();
    if (slot != GAME_NONE) {
        record               = &g_ActorSlots[slot];
        record->header.flags = 1;
        record->type         = type;
    }
}
