#include "area077_14.h"

/* func_801F61F0 */
MATCH void Actor_InitSlot(s32 type) {
    SpawnedActor* record;
    u8            slot;

    slot = Actor_FindFreeSlot();
    if (slot != GAME_NONE) {
        record               = &g_SpawnedActors[slot];
        record->header.flags = 1;
        record->type         = type;
    }
}
