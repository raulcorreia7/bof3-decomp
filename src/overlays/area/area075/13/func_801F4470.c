#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4470(void) {
    u8* p;

    SYS_ClearFlag(g_SceneEventFlags, 0x41);
    if (g_SceneState.scenario_id == 10) {
        SYS_SetFlag(g_SceneEventFlags - 0x50, 0);
        p                           = &D_801F58D1;
        g_Actors[*p].unk_77         = 4;
        g_Actors[*p].unk_7E         = 0;
        g_Actors[D_801F58D0].unk_77 = 5;
        g_Actors[D_801F58D0].unk_7E = 0;
        g_SceneEventMode            = 0;
        g_SceneEventStep            = 0;
        g_SceneState.state_04       = 5;
        g_SceneState.step_05        = 0;
        func_801BE1B0(5);
        g_ScriptVars[0] = 30;
    }
}
#else
INCLUDE_ASM(func_801F4470);
#endif
