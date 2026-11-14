#include "area135_14.h"

MATCH void func_801F5A44(void) {
    if (D_80143F03 == 4) {
        if (D_80143F06 == 1) {
            func_801A6C98(D_801F6BB0);
            SYS_ClearFlag(g_SceneEventFlags, 0xC);
            g_SceneEventSelection = 0;
        }
        D_80147CB8[3 * 0x10] |= 1;
    }
    if (D_80143F03 == 4 || (u8)(D_80143F03 - 6) < 2) {
        D_80147A58[3].header.flags = 1;
    }
    if (D_80143F03 == 0) {
        g_ScriptVars[3] = Actor_FindFreeSlot();
        if (g_ScriptVars[3] != GAME_NONE) {
            g_SpawnedActors[g_ScriptVars[3]].header.flags = 1;
            g_SpawnedActors[g_ScriptVars[3]].type         = 0x53;
            g_SpawnedActors[g_ScriptVars[3]].counter_18   = 0;
            g_SpawnedActors[g_ScriptVars[3]].counter_1C   = 6;
        }
        g_ScriptVars[3] = 0;
    }
}
