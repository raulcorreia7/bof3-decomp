#include "engine/game/00/game_00.h"

/* K&R call forwards a0 untouched to the callee. */

/* func_801ADCF4 */
/* Spawns a type 0x32 actor that starts on the actor in the given slot. */
MATCH void Actor_SpawnToss(u8 source_slot) {
    TASK(Actor)->param.unk_0B = Actor_FindFreeSpawned();
    if (TASK(Actor)->param.unk_0B != GAME_NONE) {
        g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 0x32;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_06       = source_slot;
    }
}
