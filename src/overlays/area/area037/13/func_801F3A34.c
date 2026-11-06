#include "area037_13.h"

MATCH s32 func_801F3A34(void) {
    /* FAKE: retail materializes the action code in v1. */
    MATCH_REG(s32, action, "v1");

    Game_SetScriptActive();
    action                           = 4;
    g_SaveData.scene_event.mode      = action;
    action                           = 11;
    g_SaveData.scene_event.selection = action;
    return 0;
}
