#include "area198_13.h"

MATCH void func_801F3854(void) {
    SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();
    if (SELF(Actor)->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 0xA7;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.x.fixed  = SELF(Actor)->pos.x.fixed;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.y.fixed  = SELF(Actor)->pos.y.fixed;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.z.fixed  = SELF(Actor)->pos.z.fixed + TO_COORD(256);
        return;
    }
    g_ScriptState->cursor -= 2;
}
