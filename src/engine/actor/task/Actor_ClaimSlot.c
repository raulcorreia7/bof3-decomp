#include "engine/slus/slus.h"

/* claims the free record slot reported by Actor_FindFreeSpawned and fills its
 * header, the two signed words, the id byte and the two halfword fields.
 */
/* func_8015CB18 */
MATCH s32 Actor_ClaimSlot(s32 raw_id, s32 raw_vx, s32 raw_selection, s32 raw_x, s32 raw_y) {
    u16 id        = raw_id;
    s8  vx        = raw_vx;
    s8  selection = raw_selection;
    s16 x         = raw_x;
    u16 y         = raw_y;
    u8  byte_value;
    s16 half_value;
    s32 slot;

    slot       = Actor_FindFreeSpawned() & BYTE_MASK;
    byte_value = id;
    half_value = x;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 6;
        g_SpawnedActors[slot].vx           = vx;
        g_SpawnedActors[slot].unk_06       = byte_value;
        g_SpawnedActors[slot].selection    = selection;
        g_SpawnedActors[slot].screen_x     = half_value;
        g_SpawnedActors[slot].screen_y     = y;
    }
    return slot;
}
