#include "area098_13.h"

MATCH void func_801F5BA0(void) {
    TASK(Actor)->param.actor_slot = Actor_FindFreeSpawned();
    if (TASK(Actor)->param.actor_slot == GAME_NONE) {
        return;
    }
    g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 0x37;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].pos.x.fixed  = TASK(Actor)->pos.x.fixed;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].pos.y.fixed  = TASK(Actor)->pos.y.fixed;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].pos.z.fixed  = TASK(Actor)->pos.z.fixed;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_2C       = 0x11D;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_06       = 0;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_07       = 0;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_29       = 2;
    g_SpawnedActors[TASK(Actor)->param.actor_slot].layer        = 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
}
