#include "area114_13.h"

/* Twin of area037/13 func_801F3ADC with the action code 0x2C and a zero
 * store to D_801448EC. */
MATCH s32 func_801F2C68(void) {
    /* FAKE: retail materializes the action code in v1. */
    MATCH_REG(s32, action, "v1");

    Game_SetScriptActive();
    action     = 44;
    D_801448EB = action;
    D_801448EC = 0;
    action     = 13;
    D_801448ED = action;
    return 0;
}
