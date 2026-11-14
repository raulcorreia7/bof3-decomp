#include "area085_13.h"

MATCH void func_801F39F4(void) {
    u8 slot;

    g_Task->param.actor_slot = Actor_FindFreeSlot();
    slot                     = g_Task->param.actor_slot;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags             = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type = 0x47;
        g_SpawnedActors[g_Task->param.actor_slot].link = 0;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
        return;
    }
    g_ScriptState->cursor -= 2;
}
