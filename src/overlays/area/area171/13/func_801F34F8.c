#include "area171_13.h"

MATCH void func_801F34F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SceneEventMode      = 0xA;
        g_SceneEventStep      = 5;
        g_SceneEventSelection = 0xFF;
    }
}
