#include "area141_13.h"

MATCH void func_801F3A38(void) {
    SYS_SetFlag(g_SceneEventFlags, 125);
    if (g_UIMessageChoice == 0) {
        Game_SetScriptActive();
        Area_ScrollStartRoute(3);
        Area_CellSetRun(D_801F4DBC, 0);
        g_SceneEventState.mode = 0x34;
        g_SceneEventState.step = 0x32;
        g_UIMessageRequest     = MSG_AREA141_005;
    } else {
        g_UIMessageRequest = MSG_AREA141_006;
    }
}
