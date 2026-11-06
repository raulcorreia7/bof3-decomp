#include "area136_13.h"

MATCH void func_801F2C94(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SceneEventMode      = 0x13;
        g_SceneEventStep      = 0;
        g_SceneEventSelection = 1;
    }
}
