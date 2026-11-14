#include "game_00.h"

/* K&R call forwards a0 untouched as the mode argument. */

MATCH void func_801ADCF4(u8 actor_slot) {
    g_Task->param.unk_0B = Actor_FindFreeSlot();
    if (g_Task->param.unk_0B != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x32;
        g_SpawnedActors[g_Task->param.actor_slot].unk_06       = actor_slot;
    }
}
