#include "area098_13.h"

MATCH void func_801F59F4(void) {
    MESSAGE_REQUEST_CLEAR();
    SYS_SetFlag(D_8014554C, 9);
    if (MENU_SELECTION_IDLE()) {
        g_ScriptVars[1] = 0;
    } else {
        SYS_SetFlag(g_SceneFlags, 26);
        g_ScriptVars[1] = 1;
    }
}
