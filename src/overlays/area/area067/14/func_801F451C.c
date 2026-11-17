#include "area067_14.h"

MATCH void func_801F451C(void) {
    if (g_Game.members[0].chr.character_id == CHAR_ID_PECO) {
        g_CurrentActor->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
        Game_SetScriptActive();
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step_05  = 0;
    } else {
        g_CurrentActor->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
    }
}
