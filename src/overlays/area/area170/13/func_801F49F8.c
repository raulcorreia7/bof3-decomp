#include "area170_13.h"

MATCH void func_801F49F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x25;
        g_SceneEventStep = 0x19;
    }
}
