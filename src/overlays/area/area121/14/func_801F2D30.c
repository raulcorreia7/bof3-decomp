#include "area121_14.h"

MATCH void func_801F2D30(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    g_CurrentActor->unk_77 = 0;
    g_CurrentActor->unk_7E = 0;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x17));
    Game_SetScriptActive();
    *g_ScriptVars         = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 4;
}
