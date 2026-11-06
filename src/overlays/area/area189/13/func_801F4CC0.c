#include "area189_13.h"

MATCH void func_801F4CC0(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x32;
        g_SceneEventStep = 1;
    }
}
