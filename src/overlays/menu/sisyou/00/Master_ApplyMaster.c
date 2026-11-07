#include "sisyou_00.h"

/* Shared state step owned by the main executable. */

/* Work-entry stock list, its selector, and the per-entry stock table. */

MATCH void Master_ApplyMaster(void) {
    u8 value;

    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    value = g_MasterActorModes[g_SceneEventSelection];
    if (value != GAME_NONE) {
        g_Actors[g_ScriptVars[3]].header.mode = value;
    }
    g_MasterStep = 0;
    g_SceneEventStep++;
}
