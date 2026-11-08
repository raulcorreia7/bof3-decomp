#include "area037_13.h"

MATCH s32 func_801F3A6C(void) {
    /* FAKE: retail materializes the action code in v1. */
    FAKE_REG(s32, action, "v1");

    Game_SetScriptActive();
    action                = 4;
    g_SceneEventMode      = action;
    action                = 12;
    g_SceneEventSelection = action;
    return 0;
}
