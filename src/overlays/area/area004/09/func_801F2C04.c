#include "area004_09.h"

MATCH void func_801F2C04(void) {
    /* FAKE: retail reaches g_SceneEventFlags as g_SceneEventMode + 0x63D, so the step byte address is kept in a register. */
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            g_SceneEventSelection = 0;
            break;
        case 1:
            g_SceneEventSelection = 1;
            break;
        default:
            return;
    }
    step  = &g_SceneEventMode;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 31);
}
