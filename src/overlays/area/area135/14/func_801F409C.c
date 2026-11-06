#include "area135_14.h"

MATCH void func_801F409C(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        SYS_SetFlag(g_SceneEventFlags, 0x37);
    } else {
        SYS_ClearFlag(g_SceneEventFlags, 0x37);
    }
}
