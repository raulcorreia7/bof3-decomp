#include "area002_09.h"

MATCH void func_801F2C04(void) {
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (g_UIMessageChoice) {
        case 0:
            g_SceneEventState.selection = 5;
            break;
        case 1:
            g_SceneEventState.selection = 4;
            break;
        default:
            return;
    }
    step  = &g_SceneEventState.mode;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 30);
}
