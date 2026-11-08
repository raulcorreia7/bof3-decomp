#include "area050_13.h"

MATCH s32 func_801F2DA0(void) {
    /* FAKE: the two byte stores take v1; the global header order otherwise
     * hands the constants v0. */
    FAKE_REG(s32, value, "v1");

    Game_SetScriptActive();
    value                 = 4;
    g_SceneEventMode      = value;
    value                 = 4;
    g_SceneEventSelection = value;
    return 0;
}
