#include "engine/slus/slus.h"

/* claims the record slot returned by Actor_FindFreeSlot and fills it: flag
 * and kind bytes, the caller's byte argument, two sign-extended byte fields and
 * three coordinate fields; a slot index of 0xFF is left untouched.
 */
MATCH s32 func_8015CC00(u8 id, s32 step, s32 selection, s32 x, s32 y, s32 z) {
    s32 actor_slot;
    u32 offset;

    actor_slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (actor_slot != GAME_NONE) {
        offset                                = actor_slot * 0x74u;
        g_SpawnedActors[actor_slot].header.flags = 1;
        g_SpawnedActors[actor_slot].type         = 0x19;
        g_SpawnedActors[actor_slot].unk_06       = id;
        g_SpawnedActors[actor_slot].scene_step   = (s8)step;
        g_SpawnedActors[actor_slot].selection    = (s8)selection;
        g_SpawnedActors[actor_slot].pos.x.fixed  = x;
        g_SpawnedActors[actor_slot].pos.y.fixed  = y;
        g_SpawnedActors[actor_slot].pos.z.fixed  = z;
    }
    return actor_slot;
}
