#include "area098_13.h"

MATCH void func_801F5BA0(void) {
    g_Task->param.actor_slot = Actor_FindFreeSpawned();
    if (g_Task->param.actor_slot == GAME_NONE) {
        return;
    }
    g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
    g_SpawnedActors[g_Task->param.actor_slot].type         = 0x37;
    g_SpawnedActors[g_Task->param.actor_slot].pos.x.fixed  = g_Task->pos.x.fixed;
    g_SpawnedActors[g_Task->param.actor_slot].pos.y.fixed  = g_Task->pos.y.fixed;
    g_SpawnedActors[g_Task->param.actor_slot].pos.z.fixed  = g_Task->pos.z.fixed;
    g_SpawnedActors[g_Task->param.actor_slot].unk_2C       = 0x11D;
    g_SpawnedActors[g_Task->param.actor_slot].unk_06       = 0;
    g_SpawnedActors[g_Task->param.actor_slot].unk_07       = 0;
    g_SpawnedActors[g_Task->param.actor_slot].unk_29       = 2;
    g_SpawnedActors[g_Task->param.actor_slot].layer        = 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
}
