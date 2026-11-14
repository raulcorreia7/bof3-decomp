#include "game_00.h"

/* The slot scanner is entered with a0 still holding the caller's argument, so
 * it is reached through a K&R declaration rather than its typed prototype. */

MATCH void func_801ADAC0(s8 actor_slot) {
    s8 value;

    g_Task->param.unk_0B = Actor_FindFreeSlot();
    if (g_Task->param.unk_0B != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x19;
        g_SpawnedActors[g_Task->param.actor_slot].unk_06       = actor_slot;
        g_SpawnedActors[g_Task->param.actor_slot].scene_step   = 0;
        value                                               = func_801ADC98();
        g_SpawnedActors[g_Task->param.actor_slot].selection    = value + 0x28;
        g_SpawnedActors[g_Task->param.actor_slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_SpawnedActors[g_Task->param.actor_slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_SpawnedActors[g_Task->param.actor_slot].pos.z.fixed  = g_Task->pos.z.fixed;
    }
}
