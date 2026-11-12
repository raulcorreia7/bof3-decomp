#include "area034_13.h"

MATCH void func_801F2C04(void) {
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            g_SceneEventSelection = 5;
            break;
        case 1:
            g_SceneEventSelection = 4;
            break;
        default:
            goto resume;
    }
    step  = &g_SceneEventMode;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 30);
resume:
    if (g_MessageChoice != 2 && g_SceneState.scenario_id == 8 && SYS_TestFlag(g_SceneFlags, 3) == 0) {
        g_SceneEventMode = 0;
        Game_SetScriptActive();
        func_801BE1B0(2);
        g_SceneState.state_04 = 2;
        g_SceneState.step_05  = 0;
    }
}
