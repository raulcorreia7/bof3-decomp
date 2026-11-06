#include "area003_13.h"

MATCH s32 func_801F2DE0(void) {
    /* FAKE: retail materializes the action code in v1. */
    MATCH_REG(s32, action, "v1");

    Game_SetScriptActive();
    action                           = 4;
    g_SaveData.scene_event.mode      = action;
    g_SaveData.scene_event.selection = 0;
    return 0;
}
