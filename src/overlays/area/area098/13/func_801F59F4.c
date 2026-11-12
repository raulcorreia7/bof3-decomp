#include "area098_13.h"

MATCH void func_801F59F4(void) {
    MESSAGE_REQUEST_CLEAR();
    SYS_SetFlag(D_8014554C, 9);
    if (MENU_SELECTION_IDLE()) {
        D_80146865 = 0;
    } else {
        SYS_SetFlag(g_SceneFlags, 26);
        D_80146865 = 1;
    }
}
