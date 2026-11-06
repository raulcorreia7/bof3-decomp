#include "area188_13.h"

MATCH void func_801F4618(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SceneEventMode      = 0x2B;
        g_SceneEventStep      = 0;
        g_SceneEventSelection = 0;
    }
}
