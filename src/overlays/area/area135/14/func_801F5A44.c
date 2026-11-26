#include "area135_14.h"

MATCH void func_801F5A44(void) {
    if (g_GameCellType == 4) {
        if (g_GameLastCellType == 1) {
            Actor_SpawnPartyFromDefRow(D_801F6BB0);
            SYS_ClearFlag(g_SceneEventFlags, 0xC);
            g_SceneEventState.selection = 0;
        }
        g_ActorTurnRamps[3].flags |= 1;
    }
    if (g_GameCellType == 4 || (u8)(g_GameCellType - 6) < 2) {
        g_PartyActors[3].header.flags = 1;
    }
    if (g_GameCellType == 0) {
        g_ScriptVars[3] = Actor_FindFreeSpawned();
        if (g_ScriptVars[3] != GAME_NONE) {
            g_SpawnedActors[g_ScriptVars[3]].header.flags = 1;
            g_SpawnedActors[g_ScriptVars[3]].type         = 0x53;
            g_SpawnedActors[g_ScriptVars[3]].counter_18   = 0;
            g_SpawnedActors[g_ScriptVars[3]].counter_1C   = 6;
        }
        g_ScriptVars[3] = 0;
    }
}
