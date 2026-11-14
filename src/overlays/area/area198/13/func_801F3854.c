#include "area198_13.h"

MATCH void func_801F3854(void) {
    g_Task->param.actor_slot = Actor_FindFreeSpawned();
    if (g_Task->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0xA7;
        g_SpawnedActors[g_Task->param.actor_slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_SpawnedActors[g_Task->param.actor_slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_SpawnedActors[g_Task->param.actor_slot].pos.z.fixed  = g_Task->pos.z.fixed + TO_COORD(256);
        return;
    }
    g_ScriptState->cursor -= 2;
}
