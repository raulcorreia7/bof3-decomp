#include "area114_13.h"

MATCH s32 func_801F2C68(void) {
    /* FAKE: retail materializes the action code in v1. */
    MATCH_REG(s32, action, "v1");

    Game_SetScriptActive();
    action     = 44;
    D_801448EB = action;
    action     = 13;
    D_801448EC = 0;
    D_801448ED = action;
    return 0;
}
