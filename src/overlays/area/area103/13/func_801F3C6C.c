#include "area103_13.h"

MATCH void func_801F3C6C(void) {
    s32 slot;

    if (*g_ScriptVars == 0xC) {
        g_Task->header.step++;
        g_AreaSceneMode                    = 0x23;
        slot                               = Actor_FindFreeSlot() & BYTE_MASK;
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].type         = 0x18;
        g_SpawnedActors[slot].header.mode  = 0x17;
        g_SpawnedActors[slot].header.step  = 0x0A;
    }
    Area_StepSceneFrame();
}
