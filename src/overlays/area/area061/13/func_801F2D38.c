#include "area061_13.h"

MATCH s32 func_801F2D38(void) {
    /* FAKE: the two byte stores take v1; the global header order otherwise
     * hands the constants v0. */
    MATCH_REG(s32, value, "v1");

    Game_SetScriptActive();
    value                            = 4;
    g_SaveData.scene_event.mode      = value;
    value                            = 1;
    g_SaveData.scene_event.selection = value;
    return 0;
}
