#include "area004_09.h"

MATCH void func_801F2C04(void) {
    /* FAKE: retail reaches g_SceneEventFlags as g_SceneEventState.mode + 0x63D, so the step byte address is kept in a register. */
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (g_UIMessageChoice) {
        case 0:
            g_SceneEventState.selection = 0;
            break;
        case 1:
            g_SceneEventState.selection = 1;
            break;
        default:
            return;
    }
    step  = &g_SceneEventState.mode;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 31);
}
