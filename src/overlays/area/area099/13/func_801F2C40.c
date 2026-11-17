#include "area099_13.h"

MATCH void func_801F2C40(void) {
    u8 slot;

    if (!(g_Task->direction & 0x1)) {
        g_Task->direction = (g_Task->direction - 1) & 0x7;
    }
    /* FAKE: retail reads SND_PlaySE as void(s32). */
    ((void (*)(s32))SND_PlaySE)(g_Task->unk_2C + 0x100);
    Actor_RequestScript(((g_Task->direction - 1) / 2) + 0x42);
    g_Game.current->u.field.flags_118 |= 0x40;
    slot                     = Actor_FindFreeSpawned();
    g_Task->param.actor_slot = slot;
    if (g_Task->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x1B;
    }
}
