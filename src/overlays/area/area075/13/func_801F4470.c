#include "area075_13.h"

/* Clears event flag 0x41 and, in scenario 10, starts the area's party transition. */
MATCH void func_801F4470(void) {
    u8* actor_id;

    SYS_ClearFlag(g_SceneEventFlags, 0x41);
    if (g_ScenarioState.scenario_id == 10) {
        SYS_SetFlag(g_SceneEventFlags - 0x50, 0);
        actor_id                   = &D_801F58D1;
        g_Actors[*actor_id].unk_77 = 4;
        g_Actors[*actor_id].unk_7E = 0;
        FAKE_BARRIER(); /* FAKE: keeps the second actor's id load below the first actor's halfword store. */
        g_Actors[D_801F58D0].unk_77 = 5;
        g_Actors[D_801F58D0].unk_7E = 0;
        g_SceneEventState.mode      = 0;
        g_SceneEventState.step      = 0;
        g_ScenarioState.state_04    = 5;
        g_ScenarioState.step        = 0;
        Scene_SetupParty(5);
        g_ScriptVars[0] = 30;
    }
}
