#include "engine/game/00/game_00.h"

/* The slot scanner is entered with a0 still holding the caller's argument, so
 * it is reached through a K&R declaration rather than its typed prototype. */

MATCH void Actor_SpawnSceneActor(s8 actor_slot) {
    s8 value;

    SELF(Actor)->param.unk_0B = Actor_FindFreeSpawned();
    if (SELF(Actor)->param.unk_0B != GAME_NONE) {
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 0x19;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_06       = actor_slot;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].vx           = 0;
        value                                                       = func_801ADC98();
        g_SpawnedActors[SELF(Actor)->param.actor_slot].selection    = value + 0x28;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.x.fixed  = SELF(Actor)->pos.x.fixed;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.y.fixed  = SELF(Actor)->pos.y.fixed;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.z.fixed  = SELF(Actor)->pos.z.fixed;
    }
}
