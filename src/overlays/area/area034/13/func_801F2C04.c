#include "area034_13.h"

MATCH void func_801F2C04(void) {
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (g_UIMessageChoice) {
        case 0:
            g_SceneEventState.selection = 5;
            break;
        case 1:
            g_SceneEventState.selection = 4;
            break;
        default:
            goto resume;
    }
    step  = &g_SceneEventState.mode;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 30);
resume:
    if (g_UIMessageChoice != 2 && g_ScenarioState.scenario_id == 8 && SYS_TestFlag(g_SceneFlags, 3) == 0) {
        g_SceneEventState.mode = 0;
        Game_SetScriptActive();
        Scene_SetupParty(2);
        g_ScenarioState.state_04 = 2;
        g_ScenarioState.step     = 0;
    }
}
