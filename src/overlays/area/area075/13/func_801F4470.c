#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4470(void) {
    u8* p;

    SYS_ClearFlag(g_SceneEventFlags, 0x41);
    if (g_ScenarioState.scenario_id == 10) {
        SYS_SetFlag(g_SceneEventFlags - 0x50, 0);
        p                           = &D_801F58D1;
        g_Actors[*p].unk_77         = 4;
        g_Actors[*p].unk_7E         = 0;
        g_Actors[D_801F58D0].unk_77 = 5;
        g_Actors[D_801F58D0].unk_7E = 0;
        g_SceneEventState.mode      = 0;
        g_SceneEventState.step      = 0;
        g_ScenarioState.state_04    = 5;
        g_ScenarioState.step_05     = 0;
        Scene_SetupParty(5);
        g_ScriptVars[0] = 30;
    }
}
#else
INCLUDE_ASM(func_801F4470);
#endif
