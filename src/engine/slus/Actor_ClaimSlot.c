#include "engine/slus/slus.h"

/* claims the free record slot reported by Actor_FindFreeSlot and fills its
 * header, the two signed words, the id byte and the two halfword fields.
 */
/* The head stays unprototyped: retail callers pass whole words and the callee narrows them itself. */
/* func_8015CB18 */
MATCH s32 Actor_ClaimSlot(id, step, selection, x, y)
u16       id;
s8        step;
s8        selection;
s16       x;
u16       y;
{
    u8  byte_value;
    s16 half_value;
    s32 slot;

    slot       = Actor_FindFreeSlot() & BYTE_MASK;
    byte_value = id;
    half_value = x;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 6;
        g_SpawnedActors[slot].scene_step   = step;
        g_SpawnedActors[slot].unk_06       = byte_value;
        g_SpawnedActors[slot].selection    = selection;
        g_SpawnedActors[slot].unk_2E       = half_value;
        g_SpawnedActors[slot].unk_30       = y;
    }
    return slot;
}
