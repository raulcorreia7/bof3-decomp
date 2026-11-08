#include "area003_13.h"

MATCH s32 func_801F2DE0(void) {
    /* FAKE: retail materializes the action code in v1. */
    FAKE_REG(s32, action, "v1");

    Game_SetScriptActive();
    action                = 4;
    g_SceneEventMode      = action;
    g_SceneEventSelection = 0;
    return 0;
}
