#include "area175_13.h"

MATCH void func_801F40AC(void) {
    u8 slot;

    g_Task->param.actor_slot = Actor_FindFreeSlot();
    slot                     = g_Task->param.actor_slot;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags                    = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type        = 0x1F;
        g_SpawnedActors[g_Task->param.actor_slot].pos.x.fixed = TO_COORD(46);
        g_SpawnedActors[g_Task->param.actor_slot].pos.y.fixed = TO_COORD(92);
        g_SpawnedActors[g_Task->param.actor_slot].pos.z.fixed = TO_COORD(416);
        return;
    }
    g_CurrentActor->unk_7E -= 2;
}
