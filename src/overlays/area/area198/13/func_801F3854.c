#include "area198_13.h"

MATCH void func_801F3854(void) {
    TASK(Actor)->param.actor_slot = Actor_FindFreeSpawned();
    if (TASK(Actor)->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 0xA7;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].pos.x.fixed  = TASK(Actor)->pos.x.fixed;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].pos.y.fixed  = TASK(Actor)->pos.y.fixed;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].pos.z.fixed  = TASK(Actor)->pos.z.fixed + TO_COORD(256);
        return;
    }
    g_ScriptState->cursor -= 2;
}
