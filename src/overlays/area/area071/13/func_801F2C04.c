#include "area071_13.h"

MATCH void func_801F2C04(void) {
    u8 actor_slot;

    actor_slot             = Actor_FindFreeSpawned();
    D_1F800000.view.raw[0] = actor_slot;
    if (actor_slot == GAME_NONE) {
        return;
    }
    g_SpawnedActors[actor_slot].header.flags     = 1;
    g_SpawnedActors[D_1F800000.view.raw[0]].type = 0x3C;
    g_SpawnedActors[D_1F800000.view.raw[0]].link = g_CurrentActor - g_Actors;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 7));
}
