#ifndef OVERLAY_WORLD00_AREA035_13_H
#define OVERLAY_WORLD00_AREA035_13_H

/* The world00/area035/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world00.h"

#define g_CurrentActor ((void*)g_CurrentActor)

static inline void Area035_SetScriptChoice(u8 choice) {
    ((Actor*)g_CurrentActor)->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    Game_SetScriptActive();
    g_ScriptVars[0]       = choice;
    g_SceneState.state_04 = 4;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 20;
}

#endif
