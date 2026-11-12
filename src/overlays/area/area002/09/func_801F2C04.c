#include "area002_09.h"

MATCH void func_801F2C04(void) {
    u8* step;

    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            g_SceneEventSelection = 5;
            break;
        case 1:
            g_SceneEventSelection = 4;
            break;
        default:
            return;
    }
    step  = &g_SceneEventMode;
    *step = 5;
    SYS_SetFlag(step + 0x63D, 30);
}
